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
struct arm_smccc_res {int a0; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smccc_smc (unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static int mvebu_comphy_smc(unsigned long function, unsigned long phys,
			    unsigned long lane, unsigned long mode)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function, phys, lane, mode, 0, 0, 0, 0, &res);

	return res.a0;
}