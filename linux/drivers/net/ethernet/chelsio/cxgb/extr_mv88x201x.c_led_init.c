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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  cphy_mdio_write (struct cphy*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int led_init(struct cphy *cphy)
{
	/* Setup the LED registers so we can turn on/off.
	 * Writing these bits maps control to another
	 * register. mmd(0x1) addr(0x7)
	 */
	cphy_mdio_write(cphy, MDIO_MMD_PCS, 0x8304, 0xdddd);
	return 0;
}