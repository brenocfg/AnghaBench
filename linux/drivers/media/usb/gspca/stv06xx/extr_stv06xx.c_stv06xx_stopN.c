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
struct sd {TYPE_1__* sensor; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int (* stop ) (struct sd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  STV_ISO_ENABLE ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct sd*) ; 
 int stv06xx_write_bridge (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stv06xx_stopN(struct gspca_dev *gspca_dev)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;

	/* stop ISO-streaming */
	err = stv06xx_write_bridge(sd, STV_ISO_ENABLE, 0);
	if (err < 0)
		goto out;

	err = sd->sensor->stop(sd);

out:
	if (err < 0)
		gspca_dbg(gspca_dev, D_STREAM, "Failed to stop stream\n");
	else
		gspca_dbg(gspca_dev, D_STREAM, "Stopped streaming\n");
}