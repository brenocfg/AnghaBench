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
struct sd {scalar_t__ subtype; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 scalar_t__ LogitechClickSmart310 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spca500_clksmart310_init (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* initialisation of spca500 based cameras is deferred */
	gspca_dbg(gspca_dev, D_STREAM, "SPCA500 init\n");
	if (sd->subtype == LogitechClickSmart310)
		spca500_clksmart310_init(gspca_dev);
/*	else
		spca500_initialise(gspca_dev); */
	gspca_dbg(gspca_dev, D_STREAM, "SPCA500 init done\n");
	return 0;
}