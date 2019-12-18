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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {TYPE_1__ hdr; int /*<<< orphan*/  session_id; } ;
struct hfi_session_set_buffers_pkt {unsigned int num_buffers; scalar_t__ buffer_type; int /*<<< orphan*/ * buffer_info; TYPE_2__ shdr; scalar_t__ extradata_size; int /*<<< orphan*/  min_buffer_size; int /*<<< orphan*/  buffer_size; } ;
struct hfi_buffer_info {int /*<<< orphan*/  extradata_addr; int /*<<< orphan*/  buffer_addr; } ;
struct hfi_buffer_desc {unsigned int num_buffers; scalar_t__ buffer_type; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  extradata_addr; scalar_t__ extradata_size; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HFI_BUFFER_OUTPUT ; 
 scalar_t__ HFI_BUFFER_OUTPUT2 ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_SET_BUFFERS ; 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

int pkt_session_set_buffers(struct hfi_session_set_buffers_pkt *pkt,
			    void *cookie, struct hfi_buffer_desc *bd)
{
	unsigned int i;

	if (!cookie || !pkt || !bd)
		return -EINVAL;

	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_BUFFERS;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->buffer_size = bd->buffer_size;
	pkt->min_buffer_size = bd->buffer_size;
	pkt->num_buffers = bd->num_buffers;

	if (bd->buffer_type == HFI_BUFFER_OUTPUT ||
	    bd->buffer_type == HFI_BUFFER_OUTPUT2) {
		struct hfi_buffer_info *bi;

		pkt->extradata_size = bd->extradata_size;
		pkt->shdr.hdr.size = sizeof(*pkt) - sizeof(u32) +
			(bd->num_buffers * sizeof(*bi));
		bi = (struct hfi_buffer_info *)pkt->buffer_info;
		for (i = 0; i < pkt->num_buffers; i++) {
			bi->buffer_addr = bd->device_addr;
			bi->extradata_addr = bd->extradata_addr;
		}
	} else {
		pkt->extradata_size = 0;
		pkt->shdr.hdr.size = sizeof(*pkt) +
			((bd->num_buffers - 1) * sizeof(u32));
		for (i = 0; i < pkt->num_buffers; i++)
			pkt->buffer_info[i] = bd->device_addr;
	}

	pkt->buffer_type = bd->buffer_type;

	return 0;
}