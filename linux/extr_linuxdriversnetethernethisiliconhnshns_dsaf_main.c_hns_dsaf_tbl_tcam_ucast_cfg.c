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
typedef  int /*<<< orphan*/  u32 ;
struct dsaf_tbl_tcam_ucast_cfg {int /*<<< orphan*/  tbl_ucast_out_port; int /*<<< orphan*/  tbl_ucast_dvc; int /*<<< orphan*/  tbl_ucast_old_en; int /*<<< orphan*/  tbl_ucast_item_vld; int /*<<< orphan*/  tbl_ucast_mac_discard; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_TCAM_UCAST_CFG_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_UCAST_CFG1_DVC_S ; 
 int /*<<< orphan*/  DSAF_TBL_UCAST_CFG1_ITEM_VLD_S ; 
 int /*<<< orphan*/  DSAF_TBL_UCAST_CFG1_MAC_DISCARD_S ; 
 int /*<<< orphan*/  DSAF_TBL_UCAST_CFG1_OLD_EN_S ; 
 int /*<<< orphan*/  DSAF_TBL_UCAST_CFG1_OUT_PORT_M ; 
 int /*<<< orphan*/  DSAF_TBL_UCAST_CFG1_OUT_PORT_S ; 
 int /*<<< orphan*/  dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_tbl_tcam_ucast_cfg(
	struct dsaf_device *dsaf_dev,
	struct dsaf_tbl_tcam_ucast_cfg *tbl_tcam_ucast)
{
	u32 ucast_cfg1;

	ucast_cfg1 = dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_UCAST_CFG_0_REG);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_MAC_DISCARD_S,
		     tbl_tcam_ucast->tbl_ucast_mac_discard);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_ITEM_VLD_S,
		     tbl_tcam_ucast->tbl_ucast_item_vld);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_OLD_EN_S,
		     tbl_tcam_ucast->tbl_ucast_old_en);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_DVC_S,
		     tbl_tcam_ucast->tbl_ucast_dvc);
	dsaf_set_field(ucast_cfg1, DSAF_TBL_UCAST_CFG1_OUT_PORT_M,
		       DSAF_TBL_UCAST_CFG1_OUT_PORT_S,
		       tbl_tcam_ucast->tbl_ucast_out_port);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_UCAST_CFG_0_REG, ucast_cfg1);
}