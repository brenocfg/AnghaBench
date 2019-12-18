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
struct tee_param {int dummy; } ;
struct tee_context {int dummy; } ;
struct optee_msg_arg {void* ret; int /*<<< orphan*/  num_params; int /*<<< orphan*/  params; int /*<<< orphan*/  cmd; int /*<<< orphan*/  ret_origin; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* TEEC_ERROR_BAD_PARAMETERS ; 
 void* TEEC_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  TEEC_ORIGIN_COMMS ; 
 int /*<<< orphan*/  kfree (struct tee_param*) ; 
 struct tee_param* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ optee_from_msg_param (struct tee_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* optee_supp_thrd_req (struct tee_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tee_param*) ; 
 scalar_t__ optee_to_msg_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tee_param*) ; 

__attribute__((used)) static void handle_rpc_supp_cmd(struct tee_context *ctx,
				struct optee_msg_arg *arg)
{
	struct tee_param *params;

	arg->ret_origin = TEEC_ORIGIN_COMMS;

	params = kmalloc_array(arg->num_params, sizeof(struct tee_param),
			       GFP_KERNEL);
	if (!params) {
		arg->ret = TEEC_ERROR_OUT_OF_MEMORY;
		return;
	}

	if (optee_from_msg_param(params, arg->num_params, arg->params)) {
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		goto out;
	}

	arg->ret = optee_supp_thrd_req(ctx, arg->cmd, arg->num_params, params);

	if (optee_to_msg_param(arg->params, arg->num_params, params))
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
out:
	kfree(params);
}