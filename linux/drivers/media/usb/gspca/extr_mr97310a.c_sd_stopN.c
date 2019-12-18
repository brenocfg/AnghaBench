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
struct sd {scalar_t__ do_lcd_stop; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcd_stop (struct gspca_dev*) ; 
 int /*<<< orphan*/  stream_stop (struct gspca_dev*) ; 
 int /*<<< orphan*/  zero_the_pointer (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	stream_stop(gspca_dev);
	/* Not all the cams need this, but even if not, probably a good idea */
	zero_the_pointer(gspca_dev);
	if (sd->do_lcd_stop)
		lcd_stop(gspca_dev);
}