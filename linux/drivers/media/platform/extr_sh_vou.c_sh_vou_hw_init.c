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
struct sh_vou_pdata {int flags; int /*<<< orphan*/  bus_fmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sh_vou_device {int /*<<< orphan*/  pix; TYPE_1__ v4l2_dev; struct sh_vou_pdata* pdata; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SH_VOU_HSYNC_LOW ; 
 int SH_VOU_PCLK_FALLING ; 
 int SH_VOU_VSYNC_LOW ; 
 int /*<<< orphan*/  VOUCR ; 
 int /*<<< orphan*/  VOUIR ; 
 int /*<<< orphan*/  VOUMSR ; 
 int /*<<< orphan*/  VOURCR ; 
 int /*<<< orphan*/  VOUSRR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int sh_vou_ntsc_mode (int /*<<< orphan*/ ) ; 
 int sh_vou_reg_a_read (struct sh_vou_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_vou_reg_a_write (struct sh_vou_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_vou_reg_ab_set (struct sh_vou_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sh_vou_reg_ab_write (struct sh_vou_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_vou_set_fmt_vid_out (struct sh_vou_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sh_vou_hw_init(struct sh_vou_device *vou_dev)
{
	struct sh_vou_pdata *pdata = vou_dev->pdata;
	u32 voucr = sh_vou_ntsc_mode(pdata->bus_fmt) << 29;
	int i = 100;

	/* Disable all IRQs */
	sh_vou_reg_a_write(vou_dev, VOUIR, 0);

	/* Reset VOU interfaces - registers unaffected */
	sh_vou_reg_a_write(vou_dev, VOUSRR, 0x101);
	while (--i && (sh_vou_reg_a_read(vou_dev, VOUSRR) & 0x101))
		udelay(1);

	if (!i)
		return -ETIMEDOUT;

	dev_dbg(vou_dev->v4l2_dev.dev, "Reset took %dus\n", 100 - i);

	if (pdata->flags & SH_VOU_PCLK_FALLING)
		voucr |= 1 << 28;
	if (pdata->flags & SH_VOU_HSYNC_LOW)
		voucr |= 1 << 27;
	if (pdata->flags & SH_VOU_VSYNC_LOW)
		voucr |= 1 << 26;
	sh_vou_reg_ab_set(vou_dev, VOUCR, voucr, 0xfc000000);

	/* Manual register side switching at first */
	sh_vou_reg_a_write(vou_dev, VOURCR, 4);
	/* Default - fixed HSYNC length, can be made configurable is required */
	sh_vou_reg_ab_write(vou_dev, VOUMSR, 0x800000);

	sh_vou_set_fmt_vid_out(vou_dev, &vou_dev->pix);

	return 0;
}