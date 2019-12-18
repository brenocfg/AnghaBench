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
struct TYPE_8__ {TYPE_6__* controller; } ;
struct usb_hcd {int /*<<< orphan*/  product_desc; TYPE_2__ self; } ;
struct TYPE_11__ {unsigned int complete; char* unlink; int /*<<< orphan*/  lost_iaa; int /*<<< orphan*/  iaa; int /*<<< orphan*/  error; int /*<<< orphan*/  normal; } ;
struct fotg210_hcd {int async_unlink; int /*<<< orphan*/  lock; TYPE_5__ stats; TYPE_4__* regs; TYPE_3__* caps; } ;
struct debug_buffer {char* output_buf; unsigned int alloc_size; int /*<<< orphan*/  bus; } ;
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  scratch ;
struct TYPE_12__ {TYPE_1__* bus; } ;
struct TYPE_10__ {int /*<<< orphan*/  intr_enable; int /*<<< orphan*/  command; int /*<<< orphan*/  status; } ;
struct TYPE_9__ {int /*<<< orphan*/  hcc_params; int /*<<< orphan*/  hcs_params; int /*<<< orphan*/  hc_capbase; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 unsigned int HC_VERSION (struct fotg210_hcd*,unsigned int) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 unsigned int dbg_command_buf (char*,int,char const*,unsigned int) ; 
 unsigned int dbg_intr_buf (char*,int,char const*,unsigned int) ; 
 unsigned int dbg_status_buf (char*,int,char const*,unsigned int) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  fotg210_read_frame_index (struct fotg210_hcd*) ; 
 unsigned int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  rh_state_string (struct fotg210_hcd*) ; 
 unsigned int scnprintf (char*,unsigned int,char const*,unsigned int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t fill_registers_buffer(struct debug_buffer *buf)
{
	struct usb_hcd *hcd;
	struct fotg210_hcd *fotg210;
	unsigned long flags;
	unsigned temp, size, i;
	char *next, scratch[80];
	static const char fmt[] = "%*s\n";
	static const char label[] = "";

	hcd = bus_to_hcd(buf->bus);
	fotg210 = hcd_to_fotg210(hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	spin_lock_irqsave(&fotg210->lock, flags);

	if (!HCD_HW_ACCESSIBLE(hcd)) {
		size = scnprintf(next, size,
				"bus %s, device %s\n"
				"%s\n"
				"SUSPENDED(no register access)\n",
				hcd->self.controller->bus->name,
				dev_name(hcd->self.controller),
				hcd->product_desc);
		goto done;
	}

	/* Capability Registers */
	i = HC_VERSION(fotg210, fotg210_readl(fotg210,
			&fotg210->caps->hc_capbase));
	temp = scnprintf(next, size,
			"bus %s, device %s\n"
			"%s\n"
			"EHCI %x.%02x, rh state %s\n",
			hcd->self.controller->bus->name,
			dev_name(hcd->self.controller),
			hcd->product_desc,
			i >> 8, i & 0x0ff, rh_state_string(fotg210));
	size -= temp;
	next += temp;

	/* FIXME interpret both types of params */
	i = fotg210_readl(fotg210, &fotg210->caps->hcs_params);
	temp = scnprintf(next, size, "structural params 0x%08x\n", i);
	size -= temp;
	next += temp;

	i = fotg210_readl(fotg210, &fotg210->caps->hcc_params);
	temp = scnprintf(next, size, "capability params 0x%08x\n", i);
	size -= temp;
	next += temp;

	/* Operational Registers */
	temp = dbg_status_buf(scratch, sizeof(scratch), label,
			fotg210_readl(fotg210, &fotg210->regs->status));
	temp = scnprintf(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = dbg_command_buf(scratch, sizeof(scratch), label,
			fotg210_readl(fotg210, &fotg210->regs->command));
	temp = scnprintf(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = dbg_intr_buf(scratch, sizeof(scratch), label,
			fotg210_readl(fotg210, &fotg210->regs->intr_enable));
	temp = scnprintf(next, size, fmt, temp, scratch);
	size -= temp;
	next += temp;

	temp = scnprintf(next, size, "uframe %04x\n",
			fotg210_read_frame_index(fotg210));
	size -= temp;
	next += temp;

	if (fotg210->async_unlink) {
		temp = scnprintf(next, size, "async unlink qh %p\n",
				fotg210->async_unlink);
		size -= temp;
		next += temp;
	}

#ifdef FOTG210_STATS
	temp = scnprintf(next, size,
			"irq normal %ld err %ld iaa %ld(lost %ld)\n",
			fotg210->stats.normal, fotg210->stats.error,
			fotg210->stats.iaa, fotg210->stats.lost_iaa);
	size -= temp;
	next += temp;

	temp = scnprintf(next, size, "complete %ld unlink %ld\n",
			fotg210->stats.complete, fotg210->stats.unlink);
	size -= temp;
	next += temp;
#endif

done:
	spin_unlock_irqrestore(&fotg210->lock, flags);

	return buf->alloc_size - size;
}