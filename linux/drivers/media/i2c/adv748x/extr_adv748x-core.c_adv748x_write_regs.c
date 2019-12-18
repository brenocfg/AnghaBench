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
struct adv748x_state {int dummy; } ;
struct adv748x_reg_value {scalar_t__ page; int /*<<< orphan*/  reg; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ADV748X_PAGE_EOR ; 
 int adv748x_write (struct adv748x_state*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv_err (struct adv748x_state*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_write_regs(struct adv748x_state *state,
			      const struct adv748x_reg_value *regs)
{
	int ret;

	for (; regs->page != ADV748X_PAGE_EOR; regs++) {
		ret = adv748x_write(state, regs->page, regs->reg, regs->value);
		if (ret < 0) {
			adv_err(state, "Error regs page: 0x%02x reg: 0x%02x\n",
				regs->page, regs->reg);
			return ret;
		}
	}

	return 0;
}