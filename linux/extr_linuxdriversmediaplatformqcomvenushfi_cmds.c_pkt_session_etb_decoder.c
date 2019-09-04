#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  session_id; TYPE_1__ hdr; } ;
struct hfi_session_empty_buffer_compressed_pkt {scalar_t__ packet_buffer; int /*<<< orphan*/  input_tag; int /*<<< orphan*/  filled_len; int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  offset; int /*<<< orphan*/  mark_data; int /*<<< orphan*/  mark_target; int /*<<< orphan*/  flags; int /*<<< orphan*/  time_stamp_lo; int /*<<< orphan*/  time_stamp_hi; TYPE_2__ shdr; } ;
struct hfi_frame_data {scalar_t__ device_addr; int /*<<< orphan*/  clnt_data; int /*<<< orphan*/  filled_len; int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  offset; int /*<<< orphan*/  mark_data; int /*<<< orphan*/  mark_target; int /*<<< orphan*/  flags; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_EMPTY_BUFFER ; 
 int /*<<< orphan*/  hash32_ptr (void*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

int pkt_session_etb_decoder(struct hfi_session_empty_buffer_compressed_pkt *pkt,
			    void *cookie, struct hfi_frame_data *in_frame)
{
	if (!cookie || !in_frame->device_addr)
		return -EINVAL;

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_EMPTY_BUFFER;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->time_stamp_hi = upper_32_bits(in_frame->timestamp);
	pkt->time_stamp_lo = lower_32_bits(in_frame->timestamp);
	pkt->flags = in_frame->flags;
	pkt->mark_target = in_frame->mark_target;
	pkt->mark_data = in_frame->mark_data;
	pkt->offset = in_frame->offset;
	pkt->alloc_len = in_frame->alloc_len;
	pkt->filled_len = in_frame->filled_len;
	pkt->input_tag = in_frame->clnt_data;
	pkt->packet_buffer = in_frame->device_addr;

	return 0;
}