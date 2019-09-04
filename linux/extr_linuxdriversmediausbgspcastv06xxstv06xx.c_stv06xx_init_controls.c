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
struct sd {TYPE_2__* sensor; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ctrl_handler; } ;
struct gspca_dev {int /*<<< orphan*/  ctrl_handler; TYPE_1__ vdev; } ;
struct TYPE_4__ {int (* init_controls ) (struct sd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct sd*) ; 

__attribute__((used)) static int stv06xx_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PROBE, "Initializing controls\n");

	gspca_dev->vdev.ctrl_handler = &gspca_dev->ctrl_handler;
	return sd->sensor->init_controls(sd);
}