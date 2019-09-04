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
struct arm_smccc_res {int /*<<< orphan*/  a0; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smccc_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static u32 __meson_sm_call(u32 cmd, u32 arg0, u32 arg1, u32 arg2,
			   u32 arg3, u32 arg4)
{
	struct arm_smccc_res res;

	arm_smccc_smc(cmd, arg0, arg1, arg2, arg3, arg4, 0, 0, &res);
	return res.a0;
}