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
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_IP_MULTICAST_CTRL ; 
 int B53_MC_FWD_EN ; 
 int B53_MII_DUMB_FWDG_EN ; 
 int /*<<< orphan*/  B53_SWITCH_CTRL ; 
 int /*<<< orphan*/  B53_SWITCH_MODE ; 
 int B53_UC_FWD_EN ; 
 int SM_SW_FWD_EN ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b53_set_forwarding(struct b53_device *dev, int enable)
{
	u8 mgmt;

	b53_read8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);

	if (enable)
		mgmt |= SM_SW_FWD_EN;
	else
		mgmt &= ~SM_SW_FWD_EN;

	b53_write8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, mgmt);

	/* Include IMP port in dumb forwarding mode
	 */
	b53_read8(dev, B53_CTRL_PAGE, B53_SWITCH_CTRL, &mgmt);
	mgmt |= B53_MII_DUMB_FWDG_EN;
	b53_write8(dev, B53_CTRL_PAGE, B53_SWITCH_CTRL, mgmt);

	/* Look at B53_UC_FWD_EN and B53_MC_FWD_EN to decide whether
	 * frames should be flooded or not.
	 */
	b53_read8(dev, B53_CTRL_PAGE, B53_IP_MULTICAST_CTRL, &mgmt);
	mgmt |= B53_UC_FWD_EN | B53_MC_FWD_EN;
	b53_write8(dev, B53_CTRL_PAGE, B53_IP_MULTICAST_CTRL, mgmt);
}