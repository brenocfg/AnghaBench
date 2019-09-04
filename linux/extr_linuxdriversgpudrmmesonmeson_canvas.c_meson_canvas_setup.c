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
typedef  int uint32_t ;
struct meson_drm {int /*<<< orphan*/  dmc; } ;

/* Variables and functions */
 unsigned int CANVAS_BLKMODE_BIT ; 
 int CANVAS_HEIGHT_BIT ; 
 int CANVAS_LUT_WR_EN ; 
 int CANVAS_WIDTH_HBIT ; 
 int CANVAS_WIDTH_LBIT ; 
 int CANVAS_WIDTH_LWID ; 
 int /*<<< orphan*/  DMC_CAV_LUT_ADDR ; 
 int /*<<< orphan*/  DMC_CAV_LUT_DATAH ; 
 int /*<<< orphan*/  DMC_CAV_LUT_DATAL ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void meson_canvas_setup(struct meson_drm *priv,
			uint32_t canvas_index, uint32_t addr,
			uint32_t stride, uint32_t height,
			unsigned int wrap,
			unsigned int blkmode)
{
	unsigned int val;

	regmap_write(priv->dmc, DMC_CAV_LUT_DATAL,
		(((addr + 7) >> 3)) |
		(((stride + 7) >> 3) << CANVAS_WIDTH_LBIT));

	regmap_write(priv->dmc, DMC_CAV_LUT_DATAH,
		((((stride + 7) >> 3) >> CANVAS_WIDTH_LWID) <<
						CANVAS_WIDTH_HBIT) |
		(height << CANVAS_HEIGHT_BIT) |
		(wrap << 22) |
		(blkmode << CANVAS_BLKMODE_BIT));

	regmap_write(priv->dmc, DMC_CAV_LUT_ADDR,
			CANVAS_LUT_WR_EN | canvas_index);

	/* Force a read-back to make sure everything is flushed. */
	regmap_read(priv->dmc, DMC_CAV_LUT_DATAH, &val);
}