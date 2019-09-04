#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_2__ {int bc_ver; } ;
struct bnx2x {TYPE_1__ common; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  link_params; } ;

/* Variables and functions */
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int PHY_FW_VER_LEN ; 
 int /*<<< orphan*/  bnx2x_get_ext_phy_fw_version (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bnx2x_vf_fill_fw_str (struct bnx2x*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void bnx2x_fill_fw_str(struct bnx2x *bp, char *buf, size_t buf_len)
{
	if (IS_PF(bp)) {
		u8 phy_fw_ver[PHY_FW_VER_LEN];

		phy_fw_ver[0] = '\0';
		bnx2x_get_ext_phy_fw_version(&bp->link_params,
					     phy_fw_ver, PHY_FW_VER_LEN);
		strlcpy(buf, bp->fw_ver, buf_len);
		snprintf(buf + strlen(bp->fw_ver), 32 - strlen(bp->fw_ver),
			 "bc %d.%d.%d%s%s",
			 (bp->common.bc_ver & 0xff0000) >> 16,
			 (bp->common.bc_ver & 0xff00) >> 8,
			 (bp->common.bc_ver & 0xff),
			 ((phy_fw_ver[0] != '\0') ? " phy " : ""), phy_fw_ver);
	} else {
		bnx2x_vf_fill_fw_str(bp, buf, buf_len);
	}
}