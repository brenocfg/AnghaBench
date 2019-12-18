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
struct cphy {int dummy; } ;

/* Variables and functions */
 int LINK_ENABLE_BIT ; 
 int /*<<< orphan*/  MDIO_CTRL2 ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  cphy_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cphy_mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int led_link(struct cphy *cphy, u32 do_enable)
{
	u32 led = 0;
#define LINK_ENABLE_BIT 0x1

	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_CTRL2, &led);

	if (do_enable & LINK_ENABLE_BIT) {
		led |= LINK_ENABLE_BIT;
		cphy_mdio_write(cphy, MDIO_MMD_PMAPMD, MDIO_CTRL2, led);
	} else {
		led &= ~LINK_ENABLE_BIT;
		cphy_mdio_write(cphy, MDIO_MMD_PMAPMD, MDIO_CTRL2, led);
	}
	return 0;
}