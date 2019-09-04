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
typedef  int u32 ;
struct powerdomain {int logicretstate_mask; int /*<<< orphan*/  pwrstctrl_offs; int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int EINVAL ; 
 int __ffs (int) ; 
 int am33xx_prm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_pwrdm_read_logic_retst(struct powerdomain *pwrdm)
{
	u32 v, m;

	m = pwrdm->logicretstate_mask;
	if (!m)
		return -EINVAL;

	v = am33xx_prm_read_reg(pwrdm->prcm_offs, pwrdm->pwrstctrl_offs);
	v &= m;
	v >>= __ffs(m);

	return v;
}