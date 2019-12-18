#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int num_frontends; TYPE_5__* fe; } ;
struct dvb_usb_adapter {int /*<<< orphan*/  dvb_adap; int /*<<< orphan*/  num_frontends_initialized; TYPE_6__ props; TYPE_4__* fe_adap; TYPE_2__* dev; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  sleep; int /*<<< orphan*/  init; } ;
struct TYPE_15__ {int id; TYPE_3__ ops; } ;
struct TYPE_13__ {int (* frontend_attach ) (struct dvb_usb_adapter*) ;int /*<<< orphan*/  (* tuner_attach ) (struct dvb_usb_adapter*) ;} ;
struct TYPE_12__ {TYPE_7__* fe; int /*<<< orphan*/  fe_sleep; int /*<<< orphan*/  fe_init; } ;
struct TYPE_10__ {TYPE_1__* desc; } ;
struct TYPE_9__ {int name; } ;

/* Variables and functions */
 int ENODEV ; 
 int dvb_create_media_graph (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_7__*) ; 
 scalar_t__ dvb_register_frontend (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  dvb_usb_fe_sleep ; 
 int /*<<< orphan*/  dvb_usb_fe_wakeup ; 
 int dvb_usb_media_device_register (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  err (char*,int,...) ; 
 int stub1 (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_usb_adapter*) ; 

int dvb_usb_adapter_frontend_init(struct dvb_usb_adapter *adap)
{
	int ret, i;

	/* register all given adapter frontends */
	for (i = 0; i < adap->props.num_frontends; i++) {

		if (adap->props.fe[i].frontend_attach == NULL) {
			err("strange: '%s' #%d,%d doesn't want to attach a frontend.",
			    adap->dev->desc->name, adap->id, i);

			return 0;
		}

		ret = adap->props.fe[i].frontend_attach(adap);
		if (ret || adap->fe_adap[i].fe == NULL) {
			/* only print error when there is no FE at all */
			if (i == 0)
				err("no frontend was attached by '%s'",
					adap->dev->desc->name);

			return 0;
		}

		adap->fe_adap[i].fe->id = i;

		/* re-assign sleep and wakeup functions */
		adap->fe_adap[i].fe_init = adap->fe_adap[i].fe->ops.init;
		adap->fe_adap[i].fe->ops.init  = dvb_usb_fe_wakeup;
		adap->fe_adap[i].fe_sleep = adap->fe_adap[i].fe->ops.sleep;
		adap->fe_adap[i].fe->ops.sleep = dvb_usb_fe_sleep;

		if (dvb_register_frontend(&adap->dvb_adap, adap->fe_adap[i].fe)) {
			err("Frontend %d registration failed.", i);
			dvb_frontend_detach(adap->fe_adap[i].fe);
			adap->fe_adap[i].fe = NULL;
			/* In error case, do not try register more FEs,
			 * still leaving already registered FEs alive. */
			if (i == 0)
				return -ENODEV;
			else
				return 0;
		}

		/* only attach the tuner if the demod is there */
		if (adap->props.fe[i].tuner_attach != NULL)
			adap->props.fe[i].tuner_attach(adap);

		adap->num_frontends_initialized++;
	}

	ret = dvb_create_media_graph(&adap->dvb_adap, true);
	if (ret)
		return ret;

	ret = dvb_usb_media_device_register(adap);

	return ret;
}