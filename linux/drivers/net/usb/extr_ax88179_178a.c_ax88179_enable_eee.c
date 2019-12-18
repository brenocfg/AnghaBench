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
typedef  int u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88179_PHY_ID ; 
 int /*<<< orphan*/  AX_ACCESS_PHY ; 
 int /*<<< orphan*/  GMII_PHY_PAGE_SELECT ; 
 int GMII_PHY_PGSEL_PAGE0 ; 
 int GMII_PHY_PGSEL_PAGE3 ; 
 int GMII_PHY_PGSEL_PAGE5 ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_PHYADDR ; 
 int /*<<< orphan*/  ax88179_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void ax88179_enable_eee(struct usbnet *dev)
{
	u16 tmp16;

	tmp16 = GMII_PHY_PGSEL_PAGE3;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &tmp16);

	tmp16 = 0x3247;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_PHYADDR, 2, &tmp16);

	tmp16 = GMII_PHY_PGSEL_PAGE5;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &tmp16);

	tmp16 = 0x0680;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_BMSR, 2, &tmp16);

	tmp16 = GMII_PHY_PGSEL_PAGE0;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &tmp16);
}