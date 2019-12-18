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
struct usb_hcd {int dummy; } ;
struct TYPE_6__ {struct fotg210_qh* qh; } ;
struct fotg210_qh {struct fotg210_qh* unlink_next; TYPE_3__ qh_next; } ;
struct fotg210_hcd {int /*<<< orphan*/  lock; struct fotg210_qh* async_unlink; TYPE_2__* async; } ;
struct debug_buffer {char* output_buf; unsigned int alloc_size; int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {struct fotg210_qh* qh; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  qh_lines (struct fotg210_hcd*,struct fotg210_qh*,char**,unsigned int*) ; 
 unsigned int scnprintf (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t fill_async_buffer(struct debug_buffer *buf)
{
	struct usb_hcd *hcd;
	struct fotg210_hcd *fotg210;
	unsigned long flags;
	unsigned temp, size;
	char *next;
	struct fotg210_qh *qh;

	hcd = bus_to_hcd(buf->bus);
	fotg210 = hcd_to_fotg210(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave(&fotg210->lock, flags);
	for (qh = fotg210->async->qh_next.qh; size > 0 && qh;
			qh = qh->qh_next.qh)
		qh_lines(fotg210, qh, &next, &size);
	if (fotg210->async_unlink && size > 0) {
		temp = scnprintf(next, size, "\nunlink =\n");
		size -= temp;
		next += temp;

		for (qh = fotg210->async_unlink; size > 0 && qh;
				qh = qh->unlink_next)
			qh_lines(fotg210, qh, &next, &size);
	}
	spin_unlock_irqrestore(&fotg210->lock, flags);

	return strlen(buf->output_buf);
}