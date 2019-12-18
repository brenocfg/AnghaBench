#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  entity; } ;
struct csiphy_config {int csid_id; scalar_t__ combo_mode; TYPE_1__* csi2; } ;
struct csiphy_device {TYPE_5__* ops; int /*<<< orphan*/  base_clk_mux; TYPE_4__* camss; TYPE_3__ subdev; TYPE_2__* fmt; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; struct csiphy_config cfg; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* lanes_enable ) (struct csiphy_device*,struct csiphy_config*,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  code; } ;
struct TYPE_6__ {int /*<<< orphan*/  lane_cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MSM_CSIPHY_PAD_SINK ; 
 int camss_get_pixel_clock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int csiphy_get_bpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int csiphy_get_lane_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct csiphy_device*,struct csiphy_config*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csiphy_stream_on(struct csiphy_device *csiphy)
{
	struct csiphy_config *cfg = &csiphy->cfg;
	u32 pixel_clock;
	u8 lane_mask = csiphy_get_lane_mask(&cfg->csi2->lane_cfg);
	u8 bpp = csiphy_get_bpp(csiphy->formats, csiphy->nformats,
				csiphy->fmt[MSM_CSIPHY_PAD_SINK].code);
	u8 val;
	int ret;

	ret = camss_get_pixel_clock(&csiphy->subdev.entity, &pixel_clock);
	if (ret) {
		dev_err(csiphy->camss->dev,
			"Cannot get CSI2 transmitter's pixel clock\n");
		return -EINVAL;
	}
	if (!pixel_clock) {
		dev_err(csiphy->camss->dev,
			"Got pixel clock == 0, cannot continue\n");
		return -EINVAL;
	}

	val = readl_relaxed(csiphy->base_clk_mux);
	if (cfg->combo_mode && (lane_mask & 0x18) == 0x18) {
		val &= ~0xf0;
		val |= cfg->csid_id << 4;
	} else {
		val &= ~0xf;
		val |= cfg->csid_id;
	}
	writel_relaxed(val, csiphy->base_clk_mux);
	wmb();

	csiphy->ops->lanes_enable(csiphy, cfg, pixel_clock, bpp, lane_mask);

	return 0;
}