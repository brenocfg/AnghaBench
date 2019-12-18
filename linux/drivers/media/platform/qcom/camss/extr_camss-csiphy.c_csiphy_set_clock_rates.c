#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct device {int dummy; } ;
struct TYPE_12__ {TYPE_5__* csi2; } ;
struct TYPE_8__ {int /*<<< orphan*/  entity; } ;
struct csiphy_device {int nclocks; long timer_clk_rate; TYPE_6__ cfg; TYPE_3__* fmt; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; struct camss_clock* clock; TYPE_2__ subdev; TYPE_1__* camss; } ;
struct camss_clock {int nfreqs; scalar_t__* freq; int /*<<< orphan*/  clk; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int num_data; } ;
struct TYPE_11__ {TYPE_4__ lane_cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  code; } ;
struct TYPE_7__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MSM_CSIPHY_PAD_SINK ; 
 int /*<<< orphan*/  camss_add_clock_margin (scalar_t__*) ; 
 int camss_get_pixel_clock (int /*<<< orphan*/ *,int*) ; 
 long clk_round_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int clk_set_rate (int /*<<< orphan*/ ,long) ; 
 int csiphy_get_bpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int csiphy_set_clock_rates(struct csiphy_device *csiphy)
{
	struct device *dev = csiphy->camss->dev;
	u32 pixel_clock;
	int i, j;
	int ret;

	ret = camss_get_pixel_clock(&csiphy->subdev.entity, &pixel_clock);
	if (ret)
		pixel_clock = 0;

	for (i = 0; i < csiphy->nclocks; i++) {
		struct camss_clock *clock = &csiphy->clock[i];

		if (!strcmp(clock->name, "csiphy0_timer") ||
		    !strcmp(clock->name, "csiphy1_timer") ||
		    !strcmp(clock->name, "csiphy2_timer")) {
			u8 bpp = csiphy_get_bpp(csiphy->formats,
					csiphy->nformats,
					csiphy->fmt[MSM_CSIPHY_PAD_SINK].code);
			u8 num_lanes = csiphy->cfg.csi2->lane_cfg.num_data;
			u64 min_rate = pixel_clock * bpp / (2 * num_lanes * 4);
			long round_rate;

			camss_add_clock_margin(&min_rate);

			for (j = 0; j < clock->nfreqs; j++)
				if (min_rate < clock->freq[j])
					break;

			if (j == clock->nfreqs) {
				dev_err(dev,
					"Pixel clock is too high for CSIPHY\n");
				return -EINVAL;
			}

			/* if sensor pixel clock is not available */
			/* set highest possible CSIPHY clock rate */
			if (min_rate == 0)
				j = clock->nfreqs - 1;

			round_rate = clk_round_rate(clock->clk, clock->freq[j]);
			if (round_rate < 0) {
				dev_err(dev, "clk round rate failed: %ld\n",
					round_rate);
				return -EINVAL;
			}

			csiphy->timer_clk_rate = round_rate;

			ret = clk_set_rate(clock->clk, csiphy->timer_clk_rate);
			if (ret < 0) {
				dev_err(dev, "clk set rate failed: %d\n", ret);
				return ret;
			}
		}
	}

	return 0;
}