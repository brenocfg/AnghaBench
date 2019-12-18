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
typedef  scalar_t__ u32 ;
struct tee_shm {int dummy; } ;
struct TYPE_4__ {size_t b; scalar_t__ c; int /*<<< orphan*/  a; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
struct tee_param {TYPE_2__ u; int /*<<< orphan*/  attr; } ;
struct tee_context {int /*<<< orphan*/  teedev; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ctx; } ;
struct optee {TYPE_3__ supp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tee_shm* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPTEE_MSG_RPC_CMD_SHM_ALLOC ; 
 int /*<<< orphan*/  OPTEE_MSG_RPC_SHM_TYPE_APPL ; 
 int /*<<< orphan*/  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ optee_supp_thrd_req (struct tee_context*,int /*<<< orphan*/ ,int,struct tee_param*) ; 
 struct optee* tee_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tee_shm* tee_shm_get_from_id (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct tee_shm *cmd_alloc_suppl(struct tee_context *ctx, size_t sz)
{
	u32 ret;
	struct tee_param param;
	struct optee *optee = tee_get_drvdata(ctx->teedev);
	struct tee_shm *shm;

	param.attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	param.u.value.a = OPTEE_MSG_RPC_SHM_TYPE_APPL;
	param.u.value.b = sz;
	param.u.value.c = 0;

	ret = optee_supp_thrd_req(ctx, OPTEE_MSG_RPC_CMD_SHM_ALLOC, 1, &param);
	if (ret)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&optee->supp.mutex);
	/* Increases count as secure world doesn't have a reference */
	shm = tee_shm_get_from_id(optee->supp.ctx, param.u.value.c);
	mutex_unlock(&optee->supp.mutex);
	return shm;
}