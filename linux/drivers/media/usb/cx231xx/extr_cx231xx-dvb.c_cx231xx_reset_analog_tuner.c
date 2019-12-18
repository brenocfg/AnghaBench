#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_tuner_ops {int (* init ) (TYPE_3__*) ;} ;
struct cx231xx {int xc_fw_load_done; int /*<<< orphan*/  dev; TYPE_2__* dvb; } ;
struct TYPE_4__ {struct dvb_tuner_ops tuner_ops; } ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct TYPE_5__ {TYPE_3__** frontend; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_3__*) ; 

int cx231xx_reset_analog_tuner(struct cx231xx *dev)
{
	int status = 0;

	if (dev->dvb && dev->dvb->frontend[0]) {

		struct dvb_tuner_ops *dops = &dev->dvb->frontend[0]->ops.tuner_ops;

		if (dops->init != NULL && !dev->xc_fw_load_done) {

			dev_dbg(dev->dev,
				"Reloading firmware for XC5000\n");
			status = dops->init(dev->dvb->frontend[0]);
			if (status == 0) {
				dev->xc_fw_load_done = 1;
				dev_dbg(dev->dev,
					"XC5000 firmware download completed\n");
			} else {
				dev->xc_fw_load_done = 0;
				dev_dbg(dev->dev,
					"XC5000 firmware download failed !!!\n");
			}
		}

	}

	return status;
}