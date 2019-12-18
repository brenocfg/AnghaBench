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
struct mii_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_PHYSID2 ; 
 int sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int,int) ; 

__attribute__((used)) static int marvell88e1111_init(struct mii_phy* phy)
{
	u16 rev;

	/* magic init sequence for rev 0 */
	rev = sungem_phy_read(phy, MII_PHYSID2) & 0x000f;
	if (rev == 0) {
		sungem_phy_write(phy, 0x1d, 0x000a);
		sungem_phy_write(phy, 0x1e, 0x0821);

		sungem_phy_write(phy, 0x1d, 0x0006);
		sungem_phy_write(phy, 0x1e, 0x8600);

		sungem_phy_write(phy, 0x1d, 0x000b);
		sungem_phy_write(phy, 0x1e, 0x0100);

		sungem_phy_write(phy, 0x1d, 0x0004);
		sungem_phy_write(phy, 0x1e, 0x4850);
	}
	return 0;
}