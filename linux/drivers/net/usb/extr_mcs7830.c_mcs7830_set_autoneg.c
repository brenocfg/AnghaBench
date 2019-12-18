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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int MCS7830_MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mcs7830_write_phy (struct usbnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mcs7830_set_autoneg(struct usbnet *dev, int ptrUserPhyMode)
{
	int ret;
	/* Enable all media types */
	ret = mcs7830_write_phy(dev, MII_ADVERTISE, MCS7830_MII_ADVERTISE);

	/* First reset BMCR */
	if (!ret)
		ret = mcs7830_write_phy(dev, MII_BMCR, 0x0000);
	/* Enable Auto Neg */
	if (!ret)
		ret = mcs7830_write_phy(dev, MII_BMCR, BMCR_ANENABLE);
	/* Restart Auto Neg (Keep the Enable Auto Neg Bit Set) */
	if (!ret)
		ret = mcs7830_write_phy(dev, MII_BMCR,
				BMCR_ANENABLE | BMCR_ANRESTART	);
	return ret;
}