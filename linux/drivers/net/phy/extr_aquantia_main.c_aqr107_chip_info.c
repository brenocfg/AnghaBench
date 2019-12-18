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
typedef  int /*<<< orphan*/  u8 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int /*<<< orphan*/  VEND1_GLOBAL_FW_ID ; 
 int /*<<< orphan*/  VEND1_GLOBAL_FW_ID_MAJOR ; 
 int /*<<< orphan*/  VEND1_GLOBAL_FW_ID_MINOR ; 
 int /*<<< orphan*/  VEND1_GLOBAL_RSVD_STAT1 ; 
 int /*<<< orphan*/  VEND1_GLOBAL_RSVD_STAT1_FW_BUILD_ID ; 
 int /*<<< orphan*/  VEND1_GLOBAL_RSVD_STAT1_PROV_ID ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_dbg (struct phy_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aqr107_chip_info(struct phy_device *phydev)
{
	u8 fw_major, fw_minor, build_id, prov_id;
	int val;

	val = phy_read_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_FW_ID);
	if (val < 0)
		return;

	fw_major = FIELD_GET(VEND1_GLOBAL_FW_ID_MAJOR, val);
	fw_minor = FIELD_GET(VEND1_GLOBAL_FW_ID_MINOR, val);

	val = phy_read_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_RSVD_STAT1);
	if (val < 0)
		return;

	build_id = FIELD_GET(VEND1_GLOBAL_RSVD_STAT1_FW_BUILD_ID, val);
	prov_id = FIELD_GET(VEND1_GLOBAL_RSVD_STAT1_PROV_ID, val);

	phydev_dbg(phydev, "FW %u.%u, Build %u, Provisioning %u\n",
		   fw_major, fw_minor, build_id, prov_id);
}