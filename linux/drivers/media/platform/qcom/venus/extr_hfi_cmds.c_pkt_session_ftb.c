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
struct hfi_session_fill_buffer_pkt {int stream_id; int /*<<< orphan*/ * data; int /*<<< orphan*/  offset; int /*<<< orphan*/  filled_len; int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  extradata_buffer; scalar_t__ packet_buffer; int /*<<< orphan*/  output_tag; TYPE_2__ shdr; } ;
struct hfi_frame_data {scalar_t__ buffer_type; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  offset; int /*<<< orphan*/  filled_len; int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  extradata_addr; scalar_t__ device_addr; int /*<<< orphan*/  clnt_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HFI_BUFFER_OUTPUT ; 
 scalar_t__ HFI_BUFFER_OUTPUT2 ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_FILL_BUFFER ; 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

int pkt_session_ftb(struct hfi_session_fill_buffer_pkt *pkt, void *cookie,
		    struct hfi_frame_data *out_frame)
{
	if (!cookie || !out_frame || !out_frame->device_addr)
		return -EINVAL;

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_FILL_BUFFER;
	pkt->shdr.session_id = hash32_ptr(cookie);

	if (out_frame->buffer_type == HFI_BUFFER_OUTPUT)
		pkt->stream_id = 0;
	else if (out_frame->buffer_type == HFI_BUFFER_OUTPUT2)
		pkt->stream_id = 1;

	pkt->output_tag = out_frame->clnt_data;
	pkt->packet_buffer = out_frame->device_addr;
	pkt->extradata_buffer = out_frame->extradata_addr;
	pkt->alloc_len = out_frame->alloc_len;
	pkt->filled_len = out_frame->filled_len;
	pkt->offset = out_frame->offset;
	pkt->data[0] = out_frame->extradata_size;

	return 0;
}