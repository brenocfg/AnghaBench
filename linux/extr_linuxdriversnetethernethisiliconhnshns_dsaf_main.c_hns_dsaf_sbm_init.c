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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dsaf_device {TYPE_1__ ae_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 scalar_t__ DSAFV2_SRAM_INIT_OVER_M ; 
 scalar_t__ DSAF_CFG_READ_CNT ; 
 int /*<<< orphan*/  DSAF_SRAM_INIT_OVER_0_REG ; 
 scalar_t__ DSAF_SRAM_INIT_OVER_M ; 
 scalar_t__ DSAF_SRAM_INIT_OVER_S ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ dsaf_get_dev_field (struct dsaf_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hns_dsaf_rocee_bp_en (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_sbm_bp_wl_cfg (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_sbm_cfg (struct dsaf_device*) ; 
 int hns_dsaf_sbm_cfg_mib_en (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_sbm_link_sram_init_en (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsafv2_sbm_bp_wl_cfg (struct dsaf_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hns_dsaf_sbm_init(struct dsaf_device *dsaf_dev)
{
	u32 flag;
	u32 finish_msk;
	u32 cnt = 0;
	int ret;

	if (AE_IS_VER1(dsaf_dev->dsaf_ver)) {
		hns_dsaf_sbm_bp_wl_cfg(dsaf_dev);
		finish_msk = DSAF_SRAM_INIT_OVER_M;
	} else {
		hns_dsafv2_sbm_bp_wl_cfg(dsaf_dev);
		finish_msk = DSAFV2_SRAM_INIT_OVER_M;
	}

	/* enable sbm chanel, disable sbm chanel shcut function*/
	hns_dsaf_sbm_cfg(dsaf_dev);

	/* enable sbm mib */
	ret = hns_dsaf_sbm_cfg_mib_en(dsaf_dev);
	if (ret) {
		dev_err(dsaf_dev->dev,
			"hns_dsaf_sbm_cfg_mib_en fail,%s, ret=%d\n",
			dsaf_dev->ae_dev.name, ret);
		return ret;
	}

	/* enable sbm initial link sram */
	hns_dsaf_sbm_link_sram_init_en(dsaf_dev);

	do {
		usleep_range(200, 210);/*udelay(200);*/
		flag = dsaf_get_dev_field(dsaf_dev, DSAF_SRAM_INIT_OVER_0_REG,
					  finish_msk, DSAF_SRAM_INIT_OVER_S);
		cnt++;
	} while (flag != (finish_msk >> DSAF_SRAM_INIT_OVER_S) &&
		 cnt < DSAF_CFG_READ_CNT);

	if (flag != (finish_msk >> DSAF_SRAM_INIT_OVER_S)) {
		dev_err(dsaf_dev->dev,
			"hns_dsaf_sbm_init fail %s, flag=%d, cnt=%d\n",
			dsaf_dev->ae_dev.name, flag, cnt);
		return -ENODEV;
	}

	hns_dsaf_rocee_bp_en(dsaf_dev);

	return 0;
}