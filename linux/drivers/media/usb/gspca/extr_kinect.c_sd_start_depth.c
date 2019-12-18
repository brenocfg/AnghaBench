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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_register (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_start_depth(struct gspca_dev *gspca_dev)
{
	/* turn off IR-reset function */
	write_register(gspca_dev, 0x105, 0x00);

	/* reset depth stream */
	write_register(gspca_dev, 0x06, 0x00);
	/* Depth Stream Format 0x03: 11 bit stream | 0x02: 10 bit */
	write_register(gspca_dev, 0x12, 0x02);
	/* Depth Stream Resolution 1: standard (640x480) */
	write_register(gspca_dev, 0x13, 0x01);
	/* Depth Framerate / 0x1e (30): 30 fps */
	write_register(gspca_dev, 0x14, 0x1e);
	/* Depth Stream Control  / 2: Open Depth Stream */
	write_register(gspca_dev, 0x06, 0x02);
	/* disable depth hflip / LSB = 0: Smoothing Disabled */
	write_register(gspca_dev, 0x17, 0x00);

	return 0;
}