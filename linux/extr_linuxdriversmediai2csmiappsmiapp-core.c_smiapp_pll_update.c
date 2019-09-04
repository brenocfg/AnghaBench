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
struct smiapp_pll {int /*<<< orphan*/  pixel_rate_csi; int /*<<< orphan*/  pixel_rate_pixel_array; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  scale_m; int /*<<< orphan*/  link_freq; int /*<<< orphan*/  binning_vertical; int /*<<< orphan*/  binning_horizontal; } ;
struct smiapp_sensor {int /*<<< orphan*/  pixel_rate_csi; int /*<<< orphan*/  pixel_rate_parray; TYPE_2__* csi_format; int /*<<< orphan*/  scale_m; TYPE_1__* link_freq; int /*<<< orphan*/  binning_vertical; int /*<<< orphan*/  binning_horizontal; struct smiapp_pll pll; } ;
struct TYPE_4__ {int /*<<< orphan*/  compressed; } ;
struct TYPE_3__ {size_t val; int /*<<< orphan*/ * qmenu_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smiapp_pll_try (struct smiapp_sensor*,struct smiapp_pll*) ; 

__attribute__((used)) static int smiapp_pll_update(struct smiapp_sensor *sensor)
{
	struct smiapp_pll *pll = &sensor->pll;
	int rval;

	pll->binning_horizontal = sensor->binning_horizontal;
	pll->binning_vertical = sensor->binning_vertical;
	pll->link_freq =
		sensor->link_freq->qmenu_int[sensor->link_freq->val];
	pll->scale_m = sensor->scale_m;
	pll->bits_per_pixel = sensor->csi_format->compressed;

	rval = smiapp_pll_try(sensor, pll);
	if (rval < 0)
		return rval;

	__v4l2_ctrl_s_ctrl_int64(sensor->pixel_rate_parray,
				 pll->pixel_rate_pixel_array);
	__v4l2_ctrl_s_ctrl_int64(sensor->pixel_rate_csi, pll->pixel_rate_csi);

	return 0;
}