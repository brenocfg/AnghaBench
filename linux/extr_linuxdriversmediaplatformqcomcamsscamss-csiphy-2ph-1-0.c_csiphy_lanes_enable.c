#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int pos; } ;
struct csiphy_lanes_cfg {int num_data; TYPE_3__* data; TYPE_2__ clk; } ;
struct csiphy_device {scalar_t__ base; int /*<<< orphan*/  timer_clk_rate; } ;
struct csiphy_config {int combo_mode; TYPE_1__* csi2; } ;
struct TYPE_6__ {int pos; } ;
struct TYPE_4__ {struct csiphy_lanes_cfg lane_cfg; } ;

/* Variables and functions */
 scalar_t__ CAMSS_CSI_PHY_GLBL_PWR_CFG ; 
 scalar_t__ CAMSS_CSI_PHY_GLBL_RESET ; 
 scalar_t__ CAMSS_CSI_PHY_GLBL_T_INIT_CFG0 ; 
 scalar_t__ CAMSS_CSI_PHY_INTERRUPT_CLEARn (int) ; 
 scalar_t__ CAMSS_CSI_PHY_INTERRUPT_MASKn (int) ; 
 scalar_t__ CAMSS_CSI_PHY_LNn_CFG2 (int) ; 
 scalar_t__ CAMSS_CSI_PHY_LNn_CFG3 (int) ; 
 scalar_t__ CAMSS_CSI_PHY_T_WAKEUP_CFG0 ; 
 int csiphy_settle_cnt_calc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void csiphy_lanes_enable(struct csiphy_device *csiphy,
				struct csiphy_config *cfg,
				u32 pixel_clock, u8 bpp, u8 lane_mask)
{
	struct csiphy_lanes_cfg *c = &cfg->csi2->lane_cfg;
	u8 settle_cnt;
	u8 val, l = 0;
	int i = 0;

	settle_cnt = csiphy_settle_cnt_calc(pixel_clock, bpp, c->num_data,
					    csiphy->timer_clk_rate);

	writel_relaxed(0x1, csiphy->base +
		       CAMSS_CSI_PHY_GLBL_T_INIT_CFG0);
	writel_relaxed(0x1, csiphy->base +
		       CAMSS_CSI_PHY_T_WAKEUP_CFG0);

	val = 0x1;
	val |= lane_mask << 1;
	writel_relaxed(val, csiphy->base + CAMSS_CSI_PHY_GLBL_PWR_CFG);

	val = cfg->combo_mode << 4;
	writel_relaxed(val, csiphy->base + CAMSS_CSI_PHY_GLBL_RESET);

	for (i = 0; i <= c->num_data; i++) {
		if (i == c->num_data)
			l = c->clk.pos;
		else
			l = c->data[i].pos;

		writel_relaxed(0x10, csiphy->base +
			       CAMSS_CSI_PHY_LNn_CFG2(l));
		writel_relaxed(settle_cnt, csiphy->base +
			       CAMSS_CSI_PHY_LNn_CFG3(l));
		writel_relaxed(0x3f, csiphy->base +
			       CAMSS_CSI_PHY_INTERRUPT_MASKn(l));
		writel_relaxed(0x3f, csiphy->base +
			       CAMSS_CSI_PHY_INTERRUPT_CLEARn(l));
	}
}