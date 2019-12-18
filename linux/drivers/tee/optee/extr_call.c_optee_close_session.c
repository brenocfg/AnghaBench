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
typedef  int /*<<< orphan*/  u32 ;
struct tee_shm {int dummy; } ;
struct tee_context {struct optee_context_data* data; } ;
struct optee_session {int /*<<< orphan*/  list_node; } ;
struct optee_msg_arg {int /*<<< orphan*/  session; int /*<<< orphan*/  cmd; } ;
struct optee_context_data {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tee_shm*) ; 
 int /*<<< orphan*/  OPTEE_MSG_CMD_CLOSE_SESSION ; 
 int PTR_ERR (struct tee_shm*) ; 
 struct optee_session* find_session (struct optee_context_data*,int /*<<< orphan*/ ) ; 
 struct tee_shm* get_msg_arg (struct tee_context*,int /*<<< orphan*/ ,struct optee_msg_arg**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct optee_session*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optee_do_call_with_arg (struct tee_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_shm_free (struct tee_shm*) ; 

int optee_close_session(struct tee_context *ctx, u32 session)
{
	struct optee_context_data *ctxdata = ctx->data;
	struct tee_shm *shm;
	struct optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	struct optee_session *sess;

	/* Check that the session is valid and remove it from the list */
	mutex_lock(&ctxdata->mutex);
	sess = find_session(ctxdata, session);
	if (sess)
		list_del(&sess->list_node);
	mutex_unlock(&ctxdata->mutex);
	if (!sess)
		return -EINVAL;
	kfree(sess);

	shm = get_msg_arg(ctx, 0, &msg_arg, &msg_parg);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

	msg_arg->cmd = OPTEE_MSG_CMD_CLOSE_SESSION;
	msg_arg->session = session;
	optee_do_call_with_arg(ctx, msg_parg);

	tee_shm_free(shm);
	return 0;
}