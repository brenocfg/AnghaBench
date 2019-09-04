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
struct sec_dev_info {int num_saas; scalar_t__* regs; int /*<<< orphan*/  dev; } ;
struct iommu_domain {int type; } ;

/* Variables and functions */
 int EIO ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SEC_CLK_EN_REG ; 
 scalar_t__ SEC_FSM_MAX_CNT_REG ; 
 int SEC_Q_NUM ; 
 scalar_t__ SEC_Q_WEIGHT_CFG_REG (int) ; 
 size_t SEC_SAA ; 
 int __IOMMU_DOMAIN_PAGING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct iommu_domain* iommu_get_domain_for_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_bd_endian_little (struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_cache_config (struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_clk_gate_en (struct sec_dev_info*,int) ; 
 int /*<<< orphan*/  sec_comm_cnt_cfg (struct sec_dev_info*,int) ; 
 int /*<<< orphan*/  sec_commsnap_en (struct sec_dev_info*,int) ; 
 int /*<<< orphan*/  sec_data_axird_otsd_cfg (struct sec_dev_info*,int) ; 
 int /*<<< orphan*/  sec_data_axiwr_otsd_cfg (struct sec_dev_info*,int) ; 
 int sec_ipv4_hashmask (struct sec_dev_info*,int) ; 
 int /*<<< orphan*/  sec_ipv6_hashmask (struct sec_dev_info*,int*) ; 
 int /*<<< orphan*/  sec_saa_getqm_en (struct sec_dev_info*,int,int) ; 
 int /*<<< orphan*/  sec_saa_int_mask (struct sec_dev_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_set_dbg_bd_cfg (struct sec_dev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_streamid (struct sec_dev_info*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sec_hw_init(struct sec_dev_info *info)
{
	struct iommu_domain *domain;
	u32 sec_ipv4_mask = 0;
	u32 sec_ipv6_mask[10] = {};
	u32 i, ret;

	domain = iommu_get_domain_for_dev(info->dev);

	/*
	 * Enable all available processing unit clocks.
	 * Only the first cluster is usable with translations.
	 */
	if (domain && (domain->type & __IOMMU_DOMAIN_PAGING))
		info->num_saas = 5;

	else
		info->num_saas = 10;

	writel_relaxed(GENMASK(info->num_saas - 1, 0),
		       info->regs[SEC_SAA] + SEC_CLK_EN_REG);

	/* 32 bit little endian */
	sec_bd_endian_little(info);

	sec_cache_config(info);

	/* Data axi port write and read outstanding config as per datasheet */
	sec_data_axiwr_otsd_cfg(info, 0x7);
	sec_data_axird_otsd_cfg(info, 0x7);

	/* Enable clock gating */
	sec_clk_gate_en(info, true);

	/* Set CNT_CYC register not read clear */
	sec_comm_cnt_cfg(info, false);

	/* Enable CNT_CYC */
	sec_commsnap_en(info, false);

	writel_relaxed((u32)~0, info->regs[SEC_SAA] + SEC_FSM_MAX_CNT_REG);

	ret = sec_ipv4_hashmask(info, sec_ipv4_mask);
	if (ret) {
		dev_err(info->dev, "Failed to set ipv4 hashmask %d\n", ret);
		return -EIO;
	}

	sec_ipv6_hashmask(info, sec_ipv6_mask);

	/*  do not use debug bd */
	sec_set_dbg_bd_cfg(info, 0);

	if (domain && (domain->type & __IOMMU_DOMAIN_PAGING)) {
		for (i = 0; i < SEC_Q_NUM; i++) {
			sec_streamid(info, i);
			/* Same QoS for all queues */
			writel_relaxed(0x3f,
				       info->regs[SEC_SAA] +
				       SEC_Q_WEIGHT_CFG_REG(i));
		}
	}

	for (i = 0; i < info->num_saas; i++) {
		sec_saa_getqm_en(info, i, 1);
		sec_saa_int_mask(info, i, 0);
	}

	return 0;
}