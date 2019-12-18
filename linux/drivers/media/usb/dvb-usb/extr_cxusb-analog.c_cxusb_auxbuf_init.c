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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int dummy; } ;
struct cxusb_medion_auxbuf {unsigned int len; scalar_t__ paylen; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXB ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void cxusb_auxbuf_init(struct dvb_usb_device *dvbdev,
			      struct cxusb_medion_auxbuf *auxbuf,
			      u8 *buf, unsigned int len)
{
	cxusb_vprintk(dvbdev, AUXB, "initializing auxbuf of len %u\n", len);

	auxbuf->buf = buf;
	auxbuf->len = len;
	auxbuf->paylen = 0;
}