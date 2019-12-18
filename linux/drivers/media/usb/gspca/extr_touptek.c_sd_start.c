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
struct sd {scalar_t__ this_f; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int configure (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int rc;

	sd->this_f = 0;

	rc = configure(gspca_dev);
	if (rc < 0) {
		gspca_err(gspca_dev, "Failed configure\n");
		return rc;
	}
	/* First two frames have messed up gains
	Drop them to avoid special cases in user apps? */
	return 0;
}