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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int nmodes; TYPE_2__* cam_mode; } ;
struct gspca_dev {TYPE_1__ cam; } ;
struct TYPE_4__ {int width; int height; scalar_t__ pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int wxh_to_mode(struct gspca_dev *gspca_dev,
			int width, int height, u32 pixelformat)
{
	int i;

	for (i = 0; i < gspca_dev->cam.nmodes; i++) {
		if (width == gspca_dev->cam.cam_mode[i].width
		    && height == gspca_dev->cam.cam_mode[i].height
		    && pixelformat == gspca_dev->cam.cam_mode[i].pixelformat)
			return i;
	}
	return -EINVAL;
}