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
struct dsaf_tbl_tcam_mcast_cfg {int /*<<< orphan*/ * tbl_mcast_port_msk; int /*<<< orphan*/  tbl_mcast_old_en; int /*<<< orphan*/  tbl_mcast_item_vld; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_ITEM_VLD_S ; 
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_OLD_EN_S ; 
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_VM128_112_M ; 
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_VM128_112_S ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_0_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_1_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_2_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_3_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_4_0_REG ; 
 int /*<<< orphan*/  dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_tbl_tcam_mcast_cfg(
	struct dsaf_device *dsaf_dev,
	struct dsaf_tbl_tcam_mcast_cfg *mcast)
{
	u32 mcast_cfg4;

	mcast_cfg4 = dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG);
	dsaf_set_bit(mcast_cfg4, DSAF_TBL_MCAST_CFG4_ITEM_VLD_S,
		     mcast->tbl_mcast_item_vld);
	dsaf_set_bit(mcast_cfg4, DSAF_TBL_MCAST_CFG4_OLD_EN_S,
		     mcast->tbl_mcast_old_en);
	dsaf_set_field(mcast_cfg4, DSAF_TBL_MCAST_CFG4_VM128_112_M,
		       DSAF_TBL_MCAST_CFG4_VM128_112_S,
		       mcast->tbl_mcast_port_msk[4]);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG, mcast_cfg4);

	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_3_0_REG,
		       mcast->tbl_mcast_port_msk[3]);

	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_2_0_REG,
		       mcast->tbl_mcast_port_msk[2]);

	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_1_0_REG,
		       mcast->tbl_mcast_port_msk[1]);

	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_0_0_REG,
		       mcast->tbl_mcast_port_msk[0]);
}