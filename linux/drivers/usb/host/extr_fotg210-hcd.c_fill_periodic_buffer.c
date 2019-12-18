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
union fotg210_shadow {TYPE_2__* itd; TYPE_1__* fstn; TYPE_3__* qh; scalar_t__ ptr; } ;
struct usb_hcd {int dummy; } ;
struct fotg210_qh_hw {int /*<<< orphan*/  hw_next; int /*<<< orphan*/  hw_info2; } ;
struct fotg210_hcd {unsigned int periodic_size; int /*<<< orphan*/  lock; int /*<<< orphan*/ * periodic; union fotg210_shadow* pshadow; } ;
struct debug_buffer {char* output_buf; unsigned int alloc_size; int /*<<< orphan*/  bus; } ;
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_6__ {union fotg210_shadow qh_next; int /*<<< orphan*/  period; struct fotg210_qh_hw* hw; } ;
struct TYPE_5__ {union fotg210_shadow itd_next; int /*<<< orphan*/  hw_next; } ;
struct TYPE_4__ {union fotg210_shadow fstn_next; int /*<<< orphan*/  hw_next; int /*<<< orphan*/  hw_prev; } ;

/* Variables and functions */
 unsigned int DBG_SCHED_LIMIT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QH_CMASK ; 
 int QH_SMASK ; 
 int /*<<< orphan*/  Q_NEXT_TYPE (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 
#define  Q_TYPE_FSTN 130 
#define  Q_TYPE_ITD 129 
#define  Q_TYPE_QH 128 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int hc32_to_cpu (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 
 int hc32_to_cpup (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  kfree (union fotg210_shadow*) ; 
 union fotg210_shadow* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned int output_buf_tds_dir (char*,struct fotg210_hcd*,struct fotg210_qh_hw*,TYPE_3__*,unsigned int) ; 
 unsigned int scnprintf (char*,unsigned int,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t fill_periodic_buffer(struct debug_buffer *buf)
{
	struct usb_hcd *hcd;
	struct fotg210_hcd *fotg210;
	unsigned long flags;
	union fotg210_shadow p, *seen;
	unsigned temp, size, seen_count;
	char *next;
	unsigned i;
	__hc32 tag;

	seen = kmalloc_array(DBG_SCHED_LIMIT, sizeof(*seen), GFP_ATOMIC);
	if (!seen)
		return 0;

	seen_count = 0;

	hcd = bus_to_hcd(buf->bus);
	fotg210 = hcd_to_fotg210(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	temp = scnprintf(next, size, "size = %d\n", fotg210->periodic_size);
	size -= temp;
	next += temp;

	/* dump a snapshot of the periodic schedule.
	 * iso changes, interrupt usually doesn't.
	 */
	spin_lock_irqsave(&fotg210->lock, flags);
	for (i = 0; i < fotg210->periodic_size; i++) {
		p = fotg210->pshadow[i];
		if (likely(!p.ptr))
			continue;

		tag = Q_NEXT_TYPE(fotg210, fotg210->periodic[i]);

		temp = scnprintf(next, size, "%4d: ", i);
		size -= temp;
		next += temp;

		do {
			struct fotg210_qh_hw *hw;

			switch (hc32_to_cpu(fotg210, tag)) {
			case Q_TYPE_QH:
				hw = p.qh->hw;
				temp = scnprintf(next, size, " qh%d-%04x/%p",
						p.qh->period,
						hc32_to_cpup(fotg210,
							&hw->hw_info2)
							/* uframe masks */
							& (QH_CMASK | QH_SMASK),
						p.qh);
				size -= temp;
				next += temp;
				/* don't repeat what follows this qh */
				for (temp = 0; temp < seen_count; temp++) {
					if (seen[temp].ptr != p.ptr)
						continue;
					if (p.qh->qh_next.ptr) {
						temp = scnprintf(next, size,
								" ...");
						size -= temp;
						next += temp;
					}
					break;
				}
				/* show more info the first time around */
				if (temp == seen_count) {
					temp = output_buf_tds_dir(next,
							fotg210, hw,
							p.qh, size);

					if (seen_count < DBG_SCHED_LIMIT)
						seen[seen_count++].qh = p.qh;
				} else
					temp = 0;
				tag = Q_NEXT_TYPE(fotg210, hw->hw_next);
				p = p.qh->qh_next;
				break;
			case Q_TYPE_FSTN:
				temp = scnprintf(next, size,
						" fstn-%8x/%p",
						p.fstn->hw_prev, p.fstn);
				tag = Q_NEXT_TYPE(fotg210, p.fstn->hw_next);
				p = p.fstn->fstn_next;
				break;
			case Q_TYPE_ITD:
				temp = scnprintf(next, size,
						" itd/%p", p.itd);
				tag = Q_NEXT_TYPE(fotg210, p.itd->hw_next);
				p = p.itd->itd_next;
				break;
			}
			size -= temp;
			next += temp;
		} while (p.ptr);

		temp = scnprintf(next, size, "\n");
		size -= temp;
		next += temp;
	}
	spin_unlock_irqrestore(&fotg210->lock, flags);
	kfree(seen);

	return buf->alloc_size - size;
}