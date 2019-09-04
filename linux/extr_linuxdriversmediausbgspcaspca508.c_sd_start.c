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
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_2__ cam; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	int mode;

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	reg_write(gspca_dev, 0x8500, mode);
	switch (mode) {
	case 0:
	case 1:
		reg_write(gspca_dev, 0x8700, 0x28); /* clock */
		break;
	default:
/*	case 2: */
/*	case 3: */
		reg_write(gspca_dev, 0x8700, 0x23); /* clock */
		break;
	}
	reg_write(gspca_dev, 0x8112, 0x10 | 0x20);
	return 0;
}