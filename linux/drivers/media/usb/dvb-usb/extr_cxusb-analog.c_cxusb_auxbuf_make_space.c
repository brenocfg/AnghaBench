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
struct cxusb_medion_auxbuf {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXB ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cxusb_auxbuf_head_trim (struct dvb_usb_device*,struct cxusb_medion_auxbuf*,unsigned int) ; 
 unsigned int cxusb_auxbuf_paylen (struct cxusb_medion_auxbuf*) ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static bool cxusb_auxbuf_make_space(struct dvb_usb_device *dvbdev,
				    struct cxusb_medion_auxbuf *auxbuf,
				    unsigned int howmuch)
{
	unsigned int freespace;

	if (WARN_ON(howmuch >= auxbuf->len))
		howmuch = auxbuf->len - 1;

	freespace = auxbuf->len - cxusb_auxbuf_paylen(auxbuf);

	cxusb_vprintk(dvbdev, AUXB, "freespace is %u\n", freespace);

	if (freespace >= howmuch)
		return true;

	howmuch -= freespace;

	cxusb_vprintk(dvbdev, AUXB, "will overwrite %u bytes of buffer\n",
		      howmuch);

	cxusb_auxbuf_head_trim(dvbdev, auxbuf, howmuch);

	return false;
}