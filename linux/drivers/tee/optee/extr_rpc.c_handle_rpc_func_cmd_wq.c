#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct optee_msg_arg {int num_params; int /*<<< orphan*/  ret; TYPE_3__* params; } ;
struct optee {int /*<<< orphan*/  wait_queue; } ;
struct TYPE_4__ {int a; int /*<<< orphan*/  b; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
struct TYPE_6__ {int attr; TYPE_2__ u; } ;

/* Variables and functions */
 int OPTEE_MSG_ATTR_TYPE_MASK ; 
 int OPTEE_MSG_ATTR_TYPE_VALUE_INPUT ; 
#define  OPTEE_MSG_RPC_WAIT_QUEUE_SLEEP 129 
#define  OPTEE_MSG_RPC_WAIT_QUEUE_WAKEUP 128 
 int /*<<< orphan*/  TEEC_ERROR_BAD_PARAMETERS ; 
 int /*<<< orphan*/  TEEC_SUCCESS ; 
 int /*<<< orphan*/  wq_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_rpc_func_cmd_wq(struct optee *optee,
				   struct optee_msg_arg *arg)
{
	if (arg->num_params != 1)
		goto bad;

	if ((arg->params[0].attr & OPTEE_MSG_ATTR_TYPE_MASK) !=
			OPTEE_MSG_ATTR_TYPE_VALUE_INPUT)
		goto bad;

	switch (arg->params[0].u.value.a) {
	case OPTEE_MSG_RPC_WAIT_QUEUE_SLEEP:
		wq_sleep(&optee->wait_queue, arg->params[0].u.value.b);
		break;
	case OPTEE_MSG_RPC_WAIT_QUEUE_WAKEUP:
		wq_wakeup(&optee->wait_queue, arg->params[0].u.value.b);
		break;
	default:
		goto bad;
	}

	arg->ret = TEEC_SUCCESS;
	return;
bad:
	arg->ret = TEEC_ERROR_BAD_PARAMETERS;
}