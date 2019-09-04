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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct powerdomain {int /*<<< orphan*/  pwrstctrl_offs; int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  logicretstate_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am33xx_prm_rmw_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_pwrdm_set_logic_retst(struct powerdomain *pwrdm, u8 pwrst)
{
	u32 m;

	m = pwrdm->logicretstate_mask;
	if (!m)
		return -EINVAL;

	am33xx_prm_rmw_reg_bits(m, (pwrst << __ffs(m)),
				pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);

	return 0;
}