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
struct arm_smccc_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smccc_smc (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static void sdei_smccc_smc(unsigned long function_id,
			   unsigned long arg0, unsigned long arg1,
			   unsigned long arg2, unsigned long arg3,
			   unsigned long arg4, struct arm_smccc_res *res)
{
	arm_smccc_smc(function_id, arg0, arg1, arg2, arg3, arg4, 0, 0, res);
}