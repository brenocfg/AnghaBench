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
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PB_ABORTFRAME ; 
 int /*<<< orphan*/  PB_CONTROL ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_stop(struct sd *sd)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int err;

	err = stv06xx_write_sensor(sd, PB_ABORTFRAME, 1);

	if (err < 0)
		goto out;

	/* Set bit 1 to zero */
	err = stv06xx_write_sensor(sd, PB_CONTROL, BIT(5)|BIT(3));

	gspca_dbg(gspca_dev, D_STREAM, "Halting stream\n");
out:
	return (err < 0) ? err : 0;
}