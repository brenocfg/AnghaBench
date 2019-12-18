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
struct dvb_usb_device {int dummy; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int dvbsky_stream_ctrl (struct dvb_usb_device*,int) ; 
 struct dvb_usb_device* fe_to_d (struct dvb_frontend*) ; 

__attribute__((used)) static int dvbsky_streaming_ctrl(struct dvb_frontend *fe, int onoff)
{
	struct dvb_usb_device *d = fe_to_d(fe);

	return dvbsky_stream_ctrl(d, (onoff == 0) ? 0 : 1);
}