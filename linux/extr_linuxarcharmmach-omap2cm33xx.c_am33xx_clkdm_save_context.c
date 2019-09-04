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
struct clockdomain {int /*<<< orphan*/  clkdm_offs; int /*<<< orphan*/  cm_inst; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM33XX_CLKTRCTRL_MASK ; 
 int /*<<< orphan*/  am33xx_cm_read_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am33xx_clkdm_save_context(struct clockdomain *clkdm)
{
	clkdm->context = am33xx_cm_read_reg_bits(clkdm->cm_inst,
						 clkdm->clkdm_offs,
						 AM33XX_CLKTRCTRL_MASK);

	return 0;
}