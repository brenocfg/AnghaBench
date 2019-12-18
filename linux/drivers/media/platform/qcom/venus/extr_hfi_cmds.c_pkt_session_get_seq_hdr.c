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
typedef  void* u32 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  session_id; TYPE_1__ hdr; } ;
struct hfi_session_get_sequence_header_pkt {void* packet_buffer; void* buffer_len; TYPE_2__ shdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_GET_SEQUENCE_HEADER ; 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

int pkt_session_get_seq_hdr(struct hfi_session_get_sequence_header_pkt *pkt,
			    void *cookie, u32 seq_hdr, u32 seq_hdr_len)
{
	if (!cookie || !seq_hdr || !seq_hdr_len)
		return -EINVAL;

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_GET_SEQUENCE_HEADER;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->buffer_len = seq_hdr_len;
	pkt->packet_buffer = seq_hdr;

	return 0;
}