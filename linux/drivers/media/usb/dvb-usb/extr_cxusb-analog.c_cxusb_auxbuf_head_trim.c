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
struct cxusb_medion_auxbuf {unsigned int paylen; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXB ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static void cxusb_auxbuf_head_trim(struct dvb_usb_device *dvbdev,
				   struct cxusb_medion_auxbuf *auxbuf,
				   unsigned int pos)
{
	if (pos == 0)
		return;

	if (WARN_ON(pos > auxbuf->paylen))
		return;

	cxusb_vprintk(dvbdev, AUXB,
		      "trimming auxbuf len by %u to %u\n",
		      pos, auxbuf->paylen - pos);

	memmove(auxbuf->buf, auxbuf->buf + pos, auxbuf->paylen - pos);
	auxbuf->paylen -= pos;
}