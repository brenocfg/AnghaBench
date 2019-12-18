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
typedef  int u32 ;
struct sprd_adi {scalar_t__ base; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ADI_HW_CHNS ; 
 int BIT (int) ; 
 int BIT_CLK_ALL_ON ; 
 scalar_t__ REG_ADI_CHN_ADDR (int) ; 
 scalar_t__ REG_ADI_CHN_EN ; 
 scalar_t__ REG_ADI_CHN_EN1 ; 
 scalar_t__ REG_ADI_CHN_PRIH ; 
 scalar_t__ REG_ADI_CHN_PRIL ; 
 scalar_t__ REG_ADI_GSSI_CFG0 ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sprd_adi_hw_init(struct sprd_adi *sadi)
{
	struct device_node *np = sadi->dev->of_node;
	int i, size, chn_cnt;
	const __be32 *list;
	u32 tmp;

	/* Set all channels as default priority */
	writel_relaxed(0, sadi->base + REG_ADI_CHN_PRIL);
	writel_relaxed(0, sadi->base + REG_ADI_CHN_PRIH);

	/* Set clock auto gate mode */
	tmp = readl_relaxed(sadi->base + REG_ADI_GSSI_CFG0);
	tmp &= ~BIT_CLK_ALL_ON;
	writel_relaxed(tmp, sadi->base + REG_ADI_GSSI_CFG0);

	/* Set hardware channels setting */
	list = of_get_property(np, "sprd,hw-channels", &size);
	if (!list || !size) {
		dev_info(sadi->dev, "no hw channels setting in node\n");
		return;
	}

	chn_cnt = size / 8;
	for (i = 0; i < chn_cnt; i++) {
		u32 value;
		u32 chn_id = be32_to_cpu(*list++);
		u32 chn_config = be32_to_cpu(*list++);

		/* Channel 0 and 1 are software channels */
		if (chn_id < 2)
			continue;

		writel_relaxed(chn_config, sadi->base +
			       REG_ADI_CHN_ADDR(chn_id));

		if (chn_id < 32) {
			value = readl_relaxed(sadi->base + REG_ADI_CHN_EN);
			value |= BIT(chn_id);
			writel_relaxed(value, sadi->base + REG_ADI_CHN_EN);
		} else if (chn_id < ADI_HW_CHNS) {
			value = readl_relaxed(sadi->base + REG_ADI_CHN_EN1);
			value |= BIT(chn_id - 32);
			writel_relaxed(value, sadi->base + REG_ADI_CHN_EN1);
		}
	}
}