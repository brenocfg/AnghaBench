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
struct ralink_usb_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFS_U2_PHY_AC0 ; 
 int /*<<< orphan*/  OFS_U2_PHY_AC1 ; 
 int /*<<< orphan*/  OFS_U2_PHY_AC2 ; 
 int /*<<< orphan*/  OFS_U2_PHY_ACR0 ; 
 int /*<<< orphan*/  OFS_U2_PHY_ACR3 ; 
 int /*<<< orphan*/  OFS_U2_PHY_DCR0 ; 
 int /*<<< orphan*/  OFS_U2_PHY_DTM0 ; 
 int /*<<< orphan*/  u2_phy_r32 (struct ralink_usb_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u2_phy_w32 (struct ralink_usb_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ralink_usb_phy_init(struct ralink_usb_phy *phy)
{
	u2_phy_r32(phy, OFS_U2_PHY_AC2);
	u2_phy_r32(phy, OFS_U2_PHY_ACR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);

	u2_phy_w32(phy, 0x00ffff02, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x00555502, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x00aaaa02, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x00000402, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x0048086a, OFS_U2_PHY_AC0);
	u2_phy_w32(phy, 0x4400001c, OFS_U2_PHY_AC1);
	u2_phy_w32(phy, 0xc0200000, OFS_U2_PHY_ACR3);
	u2_phy_w32(phy, 0x02000000, OFS_U2_PHY_DTM0);
}