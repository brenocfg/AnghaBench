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
struct sd {scalar_t__ bridge; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ BRIDGE_TP6800 ; 
 int TP6800_R5D_DEMOSAIC_CFG ; 
 int TP6800_R78_FORMAT ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setsharpness(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->bridge == BRIDGE_TP6800) {
		val |= 0x08;		/* grid compensation enable */
		if (gspca_dev->pixfmt.width == 640)
			reg_w(gspca_dev, TP6800_R78_FORMAT, 0x00); /* vga */
		else
			val |= 0x04;		/* scaling down enable */
		reg_w(gspca_dev, TP6800_R5D_DEMOSAIC_CFG, val);
	} else {
		val = (val << 5) | 0x08;
		reg_w(gspca_dev, 0x59, val);
	}
}