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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct bnx2x_phy {int flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int FLAGS_NOC ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_GPIO_CTRL ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_8727_power_module(struct bnx2x *bp,
				    struct bnx2x_phy *phy,
				    u8 is_power_up) {
	/* Make sure GPIOs are not using for LED mode */
	u16 val;
	/* In the GPIO register, bit 4 is use to determine if the GPIOs are
	 * operating as INPUT or as OUTPUT. Bit 1 is for input, and 0 for
	 * output
	 * Bits 0-1 determine the GPIOs value for OUTPUT in case bit 4 val is 0
	 * Bits 8-9 determine the GPIOs value for INPUT in case bit 4 val is 1
	 * where the 1st bit is the over-current(only input), and 2nd bit is
	 * for power( only output )
	 *
	 * In case of NOC feature is disabled and power is up, set GPIO control
	 *  as input to enable listening of over-current indication
	 */
	if (phy->flags & FLAGS_NOC)
		return;
	if (is_power_up)
		val = (1<<4);
	else
		/* Set GPIO control to OUTPUT, and set the power bit
		 * to according to the is_power_up
		 */
		val = (1<<1);

	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_GPIO_CTRL,
			 val);
}