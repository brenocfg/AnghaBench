#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct vfe_line {TYPE_2__* fmt; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; TYPE_1__ subdev; } ;
struct vfe_device {int nclocks; struct vfe_line* line; struct camss_clock* clock; } ;
struct camss_clock {int /*<<< orphan*/  clk; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EBUSY ; 
 int MSM_VFE_LINE_NUM ; 
 size_t MSM_VFE_PAD_SINK ; 
 int VFE_LINE_PIX ; 
 int VFE_LINE_RDI0 ; 
 int /*<<< orphan*/  camss_add_clock_margin (int*) ; 
 int camss_get_pixel_clock (int /*<<< orphan*/ *,int*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int vfe_get_bpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfe_check_clock_rates(struct vfe_device *vfe)
{
	u32 pixel_clock[MSM_VFE_LINE_NUM];
	int i, j;
	int ret;

	for (i = VFE_LINE_RDI0; i <= VFE_LINE_PIX; i++) {
		ret = camss_get_pixel_clock(&vfe->line[i].subdev.entity,
					    &pixel_clock[i]);
		if (ret)
			pixel_clock[i] = 0;
	}

	for (i = 0; i < vfe->nclocks; i++) {
		struct camss_clock *clock = &vfe->clock[i];

		if (!strcmp(clock->name, "vfe0") ||
		    !strcmp(clock->name, "vfe1")) {
			u64 min_rate = 0;
			unsigned long rate;

			for (j = VFE_LINE_RDI0; j <= VFE_LINE_PIX; j++) {
				u32 tmp;
				u8 bpp;

				if (j == VFE_LINE_PIX) {
					tmp = pixel_clock[j];
				} else {
					struct vfe_line *l = &vfe->line[j];

					bpp = vfe_get_bpp(l->formats,
						l->nformats,
						l->fmt[MSM_VFE_PAD_SINK].code);
					tmp = pixel_clock[j] * bpp / 64;
				}

				if (min_rate < tmp)
					min_rate = tmp;
			}

			camss_add_clock_margin(&min_rate);

			rate = clk_get_rate(clock->clk);
			if (rate < min_rate)
				return -EBUSY;
		}
	}

	return 0;
}