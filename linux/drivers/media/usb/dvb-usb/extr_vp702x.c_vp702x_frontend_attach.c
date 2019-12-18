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
typedef  char u8 ;
struct dvb_usb_adapter {int /*<<< orphan*/  dev; TYPE_1__* fe_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GET_SYSTEM_STRING ; 
 int /*<<< orphan*/  SET_TUNER_POWER_REQ ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  vp702x_fe_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp702x_init_pid_filter (struct dvb_usb_adapter*) ; 
 scalar_t__ vp702x_usb_inout_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  vp702x_usb_out_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp702x_frontend_attach(struct dvb_usb_adapter *adap)
{
	u8 buf[10] = { 0 };

	vp702x_usb_out_op(adap->dev, SET_TUNER_POWER_REQ, 0, 7, NULL, 0);

	if (vp702x_usb_inout_cmd(adap->dev, GET_SYSTEM_STRING, NULL, 0,
				   buf, 10, 10))
		return -EIO;

	buf[9] = '\0';
	info("system string: %s",&buf[1]);

	vp702x_init_pid_filter(adap);

	adap->fe_adap[0].fe = vp702x_fe_attach(adap->dev);
	vp702x_usb_out_op(adap->dev, SET_TUNER_POWER_REQ, 1, 7, NULL, 0);

	return 0;
}