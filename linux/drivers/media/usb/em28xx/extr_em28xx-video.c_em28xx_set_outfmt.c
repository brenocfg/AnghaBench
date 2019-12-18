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
typedef  int u8 ;
struct em28xx_v4l2 {int vinmode; int vinctl; int vbi_width; int vbi_height; int norm; TYPE_1__* format; } ;
struct em28xx {int /*<<< orphan*/  is_em25xx; struct em28xx_v4l2* v4l2; } ;
struct TYPE_2__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_R10_VINMODE ; 
 int /*<<< orphan*/  EM28XX_R11_VINCTRL ; 
 int /*<<< orphan*/  EM28XX_R27_OUTFMT ; 
 int /*<<< orphan*/  EM28XX_R34_VBI_START_H ; 
 int /*<<< orphan*/  EM28XX_R35_VBI_START_V ; 
 int /*<<< orphan*/  EM28XX_R36_VBI_WIDTH ; 
 int /*<<< orphan*/  EM28XX_R37_VBI_HEIGHT ; 
 int EM28XX_VINCTRL_VBI_RAW ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int em28xx_vbi_supported (struct em28xx*) ; 
 int em28xx_write_reg (struct em28xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int em28xx_set_outfmt(struct em28xx *dev)
{
	int ret;
	u8 fmt, vinctrl;
	struct em28xx_v4l2 *v4l2 = dev->v4l2;

	fmt = v4l2->format->reg;
	if (!dev->is_em25xx)
		fmt |= 0x20;
	/*
	 * NOTE: it's not clear if this is really needed !
	 * The datasheets say bit 5 is a reserved bit and devices seem to work
	 * fine without it. But the Windows driver sets it for em2710/50+em28xx
	 * devices and we've always been setting it, too.
	 *
	 * em2765 (em25xx, em276x/7x/8x) devices do NOT work with this bit set,
	 * it's likely used for an additional (compressed ?) format there.
	 */
	ret = em28xx_write_reg(dev, EM28XX_R27_OUTFMT, fmt);
	if (ret < 0)
		return ret;

	ret = em28xx_write_reg(dev, EM28XX_R10_VINMODE, v4l2->vinmode);
	if (ret < 0)
		return ret;

	vinctrl = v4l2->vinctl;
	if (em28xx_vbi_supported(dev) == 1) {
		vinctrl |= EM28XX_VINCTRL_VBI_RAW;
		em28xx_write_reg(dev, EM28XX_R34_VBI_START_H, 0x00);
		em28xx_write_reg(dev, EM28XX_R36_VBI_WIDTH,
				 v4l2->vbi_width / 4);
		em28xx_write_reg(dev, EM28XX_R37_VBI_HEIGHT, v4l2->vbi_height);
		if (v4l2->norm & V4L2_STD_525_60) {
			/* NTSC */
			em28xx_write_reg(dev, EM28XX_R35_VBI_START_V, 0x09);
		} else if (v4l2->norm & V4L2_STD_625_50) {
			/* PAL */
			em28xx_write_reg(dev, EM28XX_R35_VBI_START_V, 0x07);
		}
	}

	return em28xx_write_reg(dev, EM28XX_R11_VINCTRL, vinctrl);
}