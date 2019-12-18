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
struct tee_shm {int dummy; } ;
struct tee_param {int dummy; } ;
struct tee_ioctl_invoke_arg {void* ret_origin; void* ret; int /*<<< orphan*/  num_params; int /*<<< orphan*/  cancel_id; int /*<<< orphan*/  session; int /*<<< orphan*/  func; } ;
struct tee_context {struct optee_context_data* data; } ;
struct optee_session {int dummy; } ;
struct optee_msg_arg {void* ret_origin; void* ret; int /*<<< orphan*/  params; int /*<<< orphan*/  cancel_id; int /*<<< orphan*/  session; int /*<<< orphan*/  func; int /*<<< orphan*/  cmd; } ;
struct optee_context_data {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tee_shm*) ; 
 int /*<<< orphan*/  OPTEE_MSG_CMD_INVOKE_COMMAND ; 
 int PTR_ERR (struct tee_shm*) ; 
 void* TEEC_ERROR_COMMUNICATION ; 
 void* TEEC_ORIGIN_COMMS ; 
 struct optee_session* find_session (struct optee_context_data*,int /*<<< orphan*/ ) ; 
 struct tee_shm* get_msg_arg (struct tee_context*,int /*<<< orphan*/ ,struct optee_msg_arg**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ optee_do_call_with_arg (struct tee_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ optee_from_msg_param (struct tee_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int optee_to_msg_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tee_param*) ; 
 int /*<<< orphan*/  tee_shm_free (struct tee_shm*) ; 

int optee_invoke_func(struct tee_context *ctx, struct tee_ioctl_invoke_arg *arg,
		      struct tee_param *param)
{
	struct optee_context_data *ctxdata = ctx->data;
	struct tee_shm *shm;
	struct optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	struct optee_session *sess;
	int rc;

	/* Check that the session is valid */
	mutex_lock(&ctxdata->mutex);
	sess = find_session(ctxdata, arg->session);
	mutex_unlock(&ctxdata->mutex);
	if (!sess)
		return -EINVAL;

	shm = get_msg_arg(ctx, arg->num_params, &msg_arg, &msg_parg);
	if (IS_ERR(shm))
		return PTR_ERR(shm);
	msg_arg->cmd = OPTEE_MSG_CMD_INVOKE_COMMAND;
	msg_arg->func = arg->func;
	msg_arg->session = arg->session;
	msg_arg->cancel_id = arg->cancel_id;

	rc = optee_to_msg_param(msg_arg->params, arg->num_params, param);
	if (rc)
		goto out;

	if (optee_do_call_with_arg(ctx, msg_parg)) {
		msg_arg->ret = TEEC_ERROR_COMMUNICATION;
		msg_arg->ret_origin = TEEC_ORIGIN_COMMS;
	}

	if (optee_from_msg_param(param, arg->num_params, msg_arg->params)) {
		msg_arg->ret = TEEC_ERROR_COMMUNICATION;
		msg_arg->ret_origin = TEEC_ORIGIN_COMMS;
	}

	arg->ret = msg_arg->ret;
	arg->ret_origin = msg_arg->ret_origin;
out:
	tee_shm_free(shm);
	return rc;
}