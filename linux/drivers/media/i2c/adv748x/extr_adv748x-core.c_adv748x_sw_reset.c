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

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_IO_REG_01 ; 
 int /*<<< orphan*/  ADV748X_IO_REG_01_PWRDNB ; 
 int /*<<< orphan*/  ADV748X_IO_REG_01_PWRDN_MASK ; 
 int /*<<< orphan*/  ADV748X_IO_REG_F2 ; 
 int /*<<< orphan*/  ADV748X_IO_REG_F2_READ_AUTO_INC ; 
 int /*<<< orphan*/  ADV748X_IO_REG_FF ; 
 int /*<<< orphan*/  ADV748X_IO_REG_FF_MAIN_RESET ; 
 int io_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int io_write (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int adv748x_sw_reset(struct adv748x_state *state)
{
	int ret;

	ret = io_write(state, ADV748X_IO_REG_FF, ADV748X_IO_REG_FF_MAIN_RESET);
	if (ret)
		return ret;

	usleep_range(5000, 6000);

	/* Disable CEC Wakeup from power-down mode */
	ret = io_clrset(state, ADV748X_IO_REG_01, ADV748X_IO_REG_01_PWRDN_MASK,
			ADV748X_IO_REG_01_PWRDNB);
	if (ret)
		return ret;

	/* Enable I2C Read Auto-Increment for consecutive reads */
	return io_write(state, ADV748X_IO_REG_F2,
			ADV748X_IO_REG_F2_READ_AUTO_INC);
}