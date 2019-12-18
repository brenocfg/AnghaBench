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
struct optee_smc_disable_shm_cache_result {scalar_t__ status; int /*<<< orphan*/  shm_lower32; int /*<<< orphan*/  shm_upper32; } ;
struct optee_call_waiter {int dummy; } ;
struct optee {int /*<<< orphan*/  call_queue; int /*<<< orphan*/  (* invoke_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ;} ;
struct arm_smccc_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTEE_SMC_DISABLE_SHM_CACHE ; 
 scalar_t__ OPTEE_SMC_RETURN_ENOTAVAIL ; 
 scalar_t__ OPTEE_SMC_RETURN_OK ; 
 int /*<<< orphan*/  optee_cq_wait_final (int /*<<< orphan*/ *,struct optee_call_waiter*) ; 
 int /*<<< orphan*/  optee_cq_wait_for_completion (int /*<<< orphan*/ *,struct optee_call_waiter*) ; 
 int /*<<< orphan*/  optee_cq_wait_init (int /*<<< orphan*/ *,struct optee_call_waiter*) ; 
 struct tee_shm* reg_pair_to_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 
 int /*<<< orphan*/  tee_shm_free (struct tee_shm*) ; 

void optee_disable_shm_cache(struct optee *optee)
{
	struct optee_call_waiter w;

	/* We need to retry until secure world isn't busy. */
	optee_cq_wait_init(&optee->call_queue, &w);
	while (true) {
		union {
			struct arm_smccc_res smccc;
			struct optee_smc_disable_shm_cache_result result;
		} res;

		optee->invoke_fn(OPTEE_SMC_DISABLE_SHM_CACHE, 0, 0, 0, 0, 0, 0,
				 0, &res.smccc);
		if (res.result.status == OPTEE_SMC_RETURN_ENOTAVAIL)
			break; /* All shm's freed */
		if (res.result.status == OPTEE_SMC_RETURN_OK) {
			struct tee_shm *shm;

			shm = reg_pair_to_ptr(res.result.shm_upper32,
					      res.result.shm_lower32);
			tee_shm_free(shm);
		} else {
			optee_cq_wait_for_completion(&optee->call_queue, &w);
		}
	}
	optee_cq_wait_final(&optee->call_queue, &w);
}