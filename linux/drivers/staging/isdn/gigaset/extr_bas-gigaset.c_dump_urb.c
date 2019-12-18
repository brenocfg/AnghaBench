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
struct usb_iso_packet_descriptor {int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct urb {int number_of_packets; struct usb_iso_packet_descriptor* iso_frame_desc; scalar_t__ complete; scalar_t__ context; int /*<<< orphan*/  error_count; int /*<<< orphan*/  interval; int /*<<< orphan*/  start_frame; scalar_t__ setup_packet; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer_length; scalar_t__ transfer_buffer; int /*<<< orphan*/  transfer_flags; scalar_t__ hcpriv; int /*<<< orphan*/  pipe; scalar_t__ dev; } ;
typedef  enum debuglevel { ____Placeholder_debuglevel } debuglevel ;

/* Variables and functions */
 int /*<<< orphan*/  gig_dbg (int,char*,...) ; 
 int /*<<< orphan*/  usb_pipedevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipetype_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dump_urb(enum debuglevel level, const char *tag,
			    struct urb *urb)
{
#ifdef CONFIG_GIGASET_DEBUG
	int i;
	gig_dbg(level, "%s urb(0x%08lx)->{", tag, (unsigned long) urb);
	if (urb) {
		gig_dbg(level,
			"  dev=0x%08lx, pipe=%s:EP%d/DV%d:%s, "
			"hcpriv=0x%08lx, transfer_flags=0x%x,",
			(unsigned long) urb->dev,
			usb_pipetype_str(urb->pipe),
			usb_pipeendpoint(urb->pipe), usb_pipedevice(urb->pipe),
			usb_pipein(urb->pipe) ? "in" : "out",
			(unsigned long) urb->hcpriv,
			urb->transfer_flags);
		gig_dbg(level,
			"  transfer_buffer=0x%08lx[%d], actual_length=%d, "
			"setup_packet=0x%08lx,",
			(unsigned long) urb->transfer_buffer,
			urb->transfer_buffer_length, urb->actual_length,
			(unsigned long) urb->setup_packet);
		gig_dbg(level,
			"  start_frame=%d, number_of_packets=%d, interval=%d, "
			"error_count=%d,",
			urb->start_frame, urb->number_of_packets, urb->interval,
			urb->error_count);
		gig_dbg(level,
			"  context=0x%08lx, complete=0x%08lx, "
			"iso_frame_desc[]={",
			(unsigned long) urb->context,
			(unsigned long) urb->complete);
		for (i = 0; i < urb->number_of_packets; i++) {
			struct usb_iso_packet_descriptor *pifd
				= &urb->iso_frame_desc[i];
			gig_dbg(level,
				"    {offset=%u, length=%u, actual_length=%u, "
				"status=%u}",
				pifd->offset, pifd->length, pifd->actual_length,
				pifd->status);
		}
	}
	gig_dbg(level, "}}");
#endif
}