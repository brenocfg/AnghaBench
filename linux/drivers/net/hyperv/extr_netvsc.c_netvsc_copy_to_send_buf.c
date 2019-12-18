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
typedef  int u32 ;
struct rndis_message {int msg_len; } ;
struct netvsc_device {char* send_buf; unsigned int send_section_size; int pkt_align; } ;
struct hv_page_buffer {int pfn; int offset; int len; } ;
struct hv_netvsc_packet {int rmsg_pgcnt; int page_buf_cnt; int total_data_buflen; scalar_t__ cp_partial; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* phys_to_virt (int) ; 

__attribute__((used)) static void netvsc_copy_to_send_buf(struct netvsc_device *net_device,
				    unsigned int section_index,
				    u32 pend_size,
				    struct hv_netvsc_packet *packet,
				    struct rndis_message *rndis_msg,
				    struct hv_page_buffer *pb,
				    bool xmit_more)
{
	char *start = net_device->send_buf;
	char *dest = start + (section_index * net_device->send_section_size)
		     + pend_size;
	int i;
	u32 padding = 0;
	u32 page_count = packet->cp_partial ? packet->rmsg_pgcnt :
		packet->page_buf_cnt;
	u32 remain;

	/* Add padding */
	remain = packet->total_data_buflen & (net_device->pkt_align - 1);
	if (xmit_more && remain) {
		padding = net_device->pkt_align - remain;
		rndis_msg->msg_len += padding;
		packet->total_data_buflen += padding;
	}

	for (i = 0; i < page_count; i++) {
		char *src = phys_to_virt(pb[i].pfn << PAGE_SHIFT);
		u32 offset = pb[i].offset;
		u32 len = pb[i].len;

		memcpy(dest, (src + offset), len);
		dest += len;
	}

	if (padding)
		memset(dest, 0, padding);
}