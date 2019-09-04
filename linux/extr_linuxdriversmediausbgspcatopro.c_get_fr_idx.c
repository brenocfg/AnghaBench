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
struct sd {scalar_t__ bridge; scalar_t__ framerate; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ BRIDGE_TP6800 ; 
 scalar_t__* rates ; 
 scalar_t__* rates_6810 ; 

__attribute__((used)) static int get_fr_idx(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;

	if (sd->bridge == BRIDGE_TP6800) {
		for (i = 0; i < ARRAY_SIZE(rates) - 1; i++) {
			if (sd->framerate >= rates[i])
				break;
		}
		i = 6 - i;		/* 1 = 5fps .. 6 = 30fps */

		/* 640x480 * 30 fps does not work */
		if (i == 6			/* if 30 fps */
		 && gspca_dev->pixfmt.width == 640)
			i = 0x05;		/* 15 fps */
	} else {
		for (i = 0; i < ARRAY_SIZE(rates_6810) - 1; i++) {
			if (sd->framerate >= rates_6810[i])
				break;
		}
		i = 7 - i;		/* 3 = 5fps .. 7 = 30fps */

		/* 640x480 * 30 fps does not work */
		if (i == 7			/* if 30 fps */
		 && gspca_dev->pixfmt.width == 640)
			i = 6;			/* 15 fps */
		i |= 0x80;			/* clock * 1 */
	}
	return i;
}