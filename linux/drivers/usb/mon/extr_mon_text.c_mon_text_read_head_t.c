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
struct mon_text_ptr {scalar_t__ cnt; scalar_t__ limit; scalar_t__ pbuf; } ;
struct mon_reader_text {int dummy; } ;
struct mon_event_text {int xfertype; int /*<<< orphan*/  epnum; int /*<<< orphan*/  devnum; int /*<<< orphan*/  type; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  id; scalar_t__ is_in; } ;

/* Variables and functions */
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 scalar_t__ snprintf (scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mon_text_read_head_t(struct mon_reader_text *rp,
	struct mon_text_ptr *p, const struct mon_event_text *ep)
{
	char udir, utype;

	udir = (ep->is_in ? 'i' : 'o');
	switch (ep->xfertype) {
	case USB_ENDPOINT_XFER_ISOC:	utype = 'Z'; break;
	case USB_ENDPOINT_XFER_INT:	utype = 'I'; break;
	case USB_ENDPOINT_XFER_CONTROL:	utype = 'C'; break;
	default: /* PIPE_BULK */  utype = 'B';
	}
	p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
	    "%lx %u %c %c%c:%03u:%02u",
	    ep->id, ep->tstamp, ep->type,
	    utype, udir, ep->devnum, ep->epnum);
}