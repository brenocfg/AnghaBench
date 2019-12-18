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
struct kyrofb_info {int /*<<< orphan*/  PIXCLK; int /*<<< orphan*/  VSP; int /*<<< orphan*/  HSP; } ;
struct TYPE_3__ {int bits_per_pixel; int xres; int yres; } ;
struct fb_info {TYPE_1__ var; struct kyrofb_info* par; } ;
struct TYPE_4__ {int ulNextFreeVidMem; scalar_t__ ulOverlayOffset; int /*<<< orphan*/  pSTGReg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DisableRamdacOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisableVGA (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EnableRamdacOutput (int /*<<< orphan*/ ) ; 
 scalar_t__ InitialiseRamdac (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetOverlayRegisters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupVTG (int /*<<< orphan*/ ,struct kyrofb_info*) ; 
 int /*<<< orphan*/  StartVTG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopVTG (int /*<<< orphan*/ ) ; 
 TYPE_2__ deviceInfo ; 

__attribute__((used)) static int kyro_dev_video_mode_set(struct fb_info *info)
{
	struct kyrofb_info *par = info->par;

	/* Turn off display */
	StopVTG(deviceInfo.pSTGReg);
	DisableRamdacOutput(deviceInfo.pSTGReg);

	/* Bring us out of VGA and into Hi-Res mode, if not already. */
	DisableVGA(deviceInfo.pSTGReg);

	if (InitialiseRamdac(deviceInfo.pSTGReg,
			     info->var.bits_per_pixel,
			     info->var.xres, info->var.yres,
			     par->HSP, par->VSP, &par->PIXCLK) < 0)
		return -EINVAL;

	SetupVTG(deviceInfo.pSTGReg, par);

	ResetOverlayRegisters(deviceInfo.pSTGReg);

	/* Turn on display in new mode */
	EnableRamdacOutput(deviceInfo.pSTGReg);
	StartVTG(deviceInfo.pSTGReg);

	deviceInfo.ulNextFreeVidMem = info->var.xres * info->var.yres *
				      info->var.bits_per_pixel;
	deviceInfo.ulOverlayOffset = 0;

	return 0;
}