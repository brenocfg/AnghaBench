#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct reset_controller_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ rst_set_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned long) ; 
 int EINVAL ; 
 scalar_t__ clk_base ; 
 int num_special_reset ; 
 int periph_banks ; 
 TYPE_1__* periph_regs ; 
 int special_reset_assert (unsigned long) ; 
 int /*<<< orphan*/  tegra_read_chipid () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_clk_rst_assert(struct reset_controller_dev *rcdev,
		unsigned long id)
{
	/*
	 * If peripheral is on the APB bus then we must read the APB bus to
	 * flush the write operation in apb bus. This will avoid peripheral
	 * access after disabling clock. Since the reset driver has no
	 * knowledge of which reset IDs represent which devices, simply do
	 * this all the time.
	 */
	tegra_read_chipid();

	if (id < periph_banks * 32) {
		writel_relaxed(BIT(id % 32),
			       clk_base + periph_regs[id / 32].rst_set_reg);
		return 0;
	} else if (id < periph_banks * 32 + num_special_reset) {
		return special_reset_assert(id);
	}

	return -EINVAL;
}