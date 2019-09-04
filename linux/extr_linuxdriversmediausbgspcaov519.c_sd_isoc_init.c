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
struct sd {int bridge; } ;
struct TYPE_4__ {int bulk_size; } ;
struct TYPE_3__ {int width; } ;
struct gspca_dev {TYPE_2__ cam; TYPE_1__ pixfmt; } ;

/* Variables and functions */
#define  BRIDGE_OVFX2 128 
 int OVFX2_BULK_SIZE ; 

__attribute__((used)) static int sd_isoc_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->bridge) {
	case BRIDGE_OVFX2:
		if (gspca_dev->pixfmt.width != 800)
			gspca_dev->cam.bulk_size = OVFX2_BULK_SIZE;
		else
			gspca_dev->cam.bulk_size = 7 * 4096;
		break;
	}
	return 0;
}