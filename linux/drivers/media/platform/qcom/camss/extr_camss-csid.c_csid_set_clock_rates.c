#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct device {int dummy; } ;
struct csid_format {int bpp; } ;
struct TYPE_8__ {int lane_cnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct csid_device {int nclocks; TYPE_4__ phy; TYPE_3__* fmt; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; struct camss_clock* clock; TYPE_2__ subdev; TYPE_1__* camss; } ;
struct camss_clock {int nfreqs; scalar_t__* freq; int /*<<< orphan*/  clk; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  code; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MSM_CSIPHY_PAD_SINK ; 
 int /*<<< orphan*/  camss_add_clock_margin (scalar_t__*) ; 
 int camss_get_pixel_clock (int /*<<< orphan*/ *,int*) ; 
 long clk_round_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int clk_set_rate (int /*<<< orphan*/ ,long) ; 
 struct csid_format* csid_get_fmt_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int csid_set_clock_rates(struct csid_device *csid)
{
	struct device *dev = csid->camss->dev;
	u32 pixel_clock;
	int i, j;
	int ret;

	ret = camss_get_pixel_clock(&csid->subdev.entity, &pixel_clock);
	if (ret)
		pixel_clock = 0;

	for (i = 0; i < csid->nclocks; i++) {
		struct camss_clock *clock = &csid->clock[i];

		if (!strcmp(clock->name, "csi0") ||
		    !strcmp(clock->name, "csi1") ||
		    !strcmp(clock->name, "csi2") ||
		    !strcmp(clock->name, "csi3")) {
			const struct csid_format *f = csid_get_fmt_entry(
				csid->formats,
				csid->nformats,
				csid->fmt[MSM_CSIPHY_PAD_SINK].code);
			u8 num_lanes = csid->phy.lane_cnt;
			u64 min_rate = pixel_clock * f->bpp /
							(2 * num_lanes * 4);
			long rate;

			camss_add_clock_margin(&min_rate);

			for (j = 0; j < clock->nfreqs; j++)
				if (min_rate < clock->freq[j])
					break;

			if (j == clock->nfreqs) {
				dev_err(dev,
					"Pixel clock is too high for CSID\n");
				return -EINVAL;
			}

			/* if sensor pixel clock is not available */
			/* set highest possible CSID clock rate */
			if (min_rate == 0)
				j = clock->nfreqs - 1;

			rate = clk_round_rate(clock->clk, clock->freq[j]);
			if (rate < 0) {
				dev_err(dev, "clk round rate failed: %ld\n",
					rate);
				return -EINVAL;
			}

			ret = clk_set_rate(clock->clk, rate);
			if (ret < 0) {
				dev_err(dev, "clk set rate failed: %d\n", ret);
				return ret;
			}
		}
	}

	return 0;
}