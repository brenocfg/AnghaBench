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
struct wa_xfer_packet_info_hwaiso {void** PacketLength; void* wLength; int /*<<< orphan*/  bPacketType; } ;
struct wa_xfer {TYPE_1__* urb; } ;
struct wa_seg {int isoc_frame_count; int isoc_frame_offset; } ;
struct usb_iso_packet_descriptor {int /*<<< orphan*/  length; } ;
struct TYPE_2__ {struct usb_iso_packet_descriptor* iso_frame_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PacketLength ; 
 int /*<<< orphan*/  WA_XFER_ISO_PACKET_INFO ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct wa_xfer_packet_info_hwaiso*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __wa_setup_isoc_packet_descr(
		struct wa_xfer_packet_info_hwaiso *packet_desc,
		struct wa_xfer *xfer,
		struct wa_seg *seg) {
	struct usb_iso_packet_descriptor *iso_frame_desc =
		xfer->urb->iso_frame_desc;
	int frame_index;

	/* populate isoc packet descriptor. */
	packet_desc->bPacketType = WA_XFER_ISO_PACKET_INFO;
	packet_desc->wLength = cpu_to_le16(struct_size(packet_desc,
					   PacketLength,
					   seg->isoc_frame_count));
	for (frame_index = 0; frame_index < seg->isoc_frame_count;
		++frame_index) {
		int offset_index = frame_index + seg->isoc_frame_offset;
		packet_desc->PacketLength[frame_index] =
			cpu_to_le16(iso_frame_desc[offset_index].length);
	}
}