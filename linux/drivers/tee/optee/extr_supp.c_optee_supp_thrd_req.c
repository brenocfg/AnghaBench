#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u32 ;
struct tee_param {int dummy; } ;
struct tee_context {scalar_t__ supp_nowait; int /*<<< orphan*/  teedev; } ;
struct optee_supp_req {size_t num_params; int in_queue; void* ret; int /*<<< orphan*/  link; int /*<<< orphan*/  c; struct tee_param* param; void* func; } ;
struct optee_supp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ctx; int /*<<< orphan*/  reqs_c; int /*<<< orphan*/  reqs; } ;
struct optee {struct optee_supp supp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* TEEC_ERROR_COMMUNICATION ; 
 void* TEEC_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct optee_supp_req*) ; 
 struct optee_supp_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct optee* tee_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

u32 optee_supp_thrd_req(struct tee_context *ctx, u32 func, size_t num_params,
			struct tee_param *param)

{
	struct optee *optee = tee_get_drvdata(ctx->teedev);
	struct optee_supp *supp = &optee->supp;
	struct optee_supp_req *req;
	bool interruptable;
	u32 ret;

	/*
	 * Return in case there is no supplicant available and
	 * non-blocking request.
	 */
	if (!supp->ctx && ctx->supp_nowait)
		return TEEC_ERROR_COMMUNICATION;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return TEEC_ERROR_OUT_OF_MEMORY;

	init_completion(&req->c);
	req->func = func;
	req->num_params = num_params;
	req->param = param;

	/* Insert the request in the request list */
	mutex_lock(&supp->mutex);
	list_add_tail(&req->link, &supp->reqs);
	req->in_queue = true;
	mutex_unlock(&supp->mutex);

	/* Tell an eventual waiter there's a new request */
	complete(&supp->reqs_c);

	/*
	 * Wait for supplicant to process and return result, once we've
	 * returned from wait_for_completion(&req->c) successfully we have
	 * exclusive access again.
	 */
	while (wait_for_completion_interruptible(&req->c)) {
		mutex_lock(&supp->mutex);
		interruptable = !supp->ctx;
		if (interruptable) {
			/*
			 * There's no supplicant available and since the
			 * supp->mutex currently is held none can
			 * become available until the mutex released
			 * again.
			 *
			 * Interrupting an RPC to supplicant is only
			 * allowed as a way of slightly improving the user
			 * experience in case the supplicant hasn't been
			 * started yet. During normal operation the supplicant
			 * will serve all requests in a timely manner and
			 * interrupting then wouldn't make sense.
			 */
			if (req->in_queue) {
				list_del(&req->link);
				req->in_queue = false;
			}
		}
		mutex_unlock(&supp->mutex);

		if (interruptable) {
			req->ret = TEEC_ERROR_COMMUNICATION;
			break;
		}
	}

	ret = req->ret;
	kfree(req);

	return ret;
}