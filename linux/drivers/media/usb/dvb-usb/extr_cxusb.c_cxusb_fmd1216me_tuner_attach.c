#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* devices; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; TYPE_2__ props; } ;
struct dvb_usb_adapter {TYPE_5__* fe_adap; struct dvb_usb_device* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/ * sleep; } ;
struct TYPE_10__ {TYPE_3__ tuner_ops; } ;
struct TYPE_12__ {TYPE_4__ ops; } ;
struct TYPE_11__ {TYPE_6__* fe; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** warm_ids; } ;

/* Variables and functions */
 size_t MEDION_MD95700 ; 
 int /*<<< orphan*/  TUNER_PHILIPS_FMD1216ME_MK3 ; 
 int /*<<< orphan*/ * cxusb_table ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_tuner_attach ; 

__attribute__((used)) static int cxusb_fmd1216me_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *dvbdev = adap->dev;
	bool is_medion = dvbdev->props.devices[0].warm_ids[0] ==
		&cxusb_table[MEDION_MD95700];

	dvb_attach(simple_tuner_attach, adap->fe_adap[0].fe,
		   &dvbdev->i2c_adap, 0x61,
		   TUNER_PHILIPS_FMD1216ME_MK3);

	if (is_medion && adap->fe_adap[0].fe)
		/*
		 * make sure that DVB core won't put to sleep (reset, really)
		 * tuner when we might be open in analog mode
		 */
		adap->fe_adap[0].fe->ops.tuner_ops.sleep = NULL;

	return 0;
}