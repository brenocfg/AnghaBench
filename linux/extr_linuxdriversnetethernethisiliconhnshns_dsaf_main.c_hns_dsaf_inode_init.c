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
struct dsaf_device {scalar_t__ dsaf_tc_mode; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT1_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT1_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT2_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT2_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT3_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT3_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT4_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT4_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT5_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_INODE_IN_PORT5_NUM_S ; 
 int DSAF_INODE_IN_PORT_NUM_0_REG ; 
 int /*<<< orphan*/  DSAF_INODE_IN_PORT_NUM_M ; 
 int /*<<< orphan*/  DSAF_INODE_IN_PORT_NUM_S ; 
 int DSAF_INODE_NUM ; 
 int DSAF_INODE_PRI_TC_CFG_0_REG ; 
 int DSAF_PORT_TYPE_NUM ; 
 int DSAF_XGE_NUM ; 
 int HNS_DSAF_I4TC_CFG ; 
 int HNS_DSAF_I8TC_CFG ; 
 scalar_t__ HRD_DSAF_4TC_MODE ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct dsaf_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int,int) ; 

__attribute__((used)) static void hns_dsaf_inode_init(struct dsaf_device *dsaf_dev)
{
	u32 reg;
	u32 tc_cfg;
	u32 i;

	if (dsaf_dev->dsaf_tc_mode == HRD_DSAF_4TC_MODE)
		tc_cfg = HNS_DSAF_I4TC_CFG;
	else
		tc_cfg = HNS_DSAF_I8TC_CFG;

	if (AE_IS_VER1(dsaf_dev->dsaf_ver)) {
		for (i = 0; i < DSAF_INODE_NUM; i++) {
			reg = DSAF_INODE_IN_PORT_NUM_0_REG + 0x80 * i;
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAF_INODE_IN_PORT_NUM_M,
					   DSAF_INODE_IN_PORT_NUM_S,
					   i % DSAF_XGE_NUM);
		}
	} else {
		for (i = 0; i < DSAF_PORT_TYPE_NUM; i++) {
			reg = DSAF_INODE_IN_PORT_NUM_0_REG + 0x80 * i;
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAF_INODE_IN_PORT_NUM_M,
					   DSAF_INODE_IN_PORT_NUM_S, 0);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT1_NUM_M,
					   DSAFV2_INODE_IN_PORT1_NUM_S, 1);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT2_NUM_M,
					   DSAFV2_INODE_IN_PORT2_NUM_S, 2);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT3_NUM_M,
					   DSAFV2_INODE_IN_PORT3_NUM_S, 3);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT4_NUM_M,
					   DSAFV2_INODE_IN_PORT4_NUM_S, 4);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT5_NUM_M,
					   DSAFV2_INODE_IN_PORT5_NUM_S, 5);
		}
	}
	for (i = 0; i < DSAF_INODE_NUM; i++) {
		reg = DSAF_INODE_PRI_TC_CFG_0_REG + 0x80 * i;
		dsaf_write_dev(dsaf_dev, reg, tc_cfg);
	}
}