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
typedef  int u64 ;
typedef  int u32 ;
struct packet_msg_prot {void* addr; void* value; void* ctl; } ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int CFG_BASE ; 
 int GOYA_PKT_CTL_EB_SHIFT ; 
 int GOYA_PKT_CTL_MB_SHIFT ; 
 int GOYA_PKT_CTL_OPCODE_SHIFT ; 
 int PACKET_MSG_PROT ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int) ; 
 int mmPCIE_DBI_MSIX_DOORBELL_OFF ; 

void goya_add_end_of_cb_packets(struct hl_device *hdev, u64 kernel_address,
				u32 len, u64 cq_addr, u32 cq_val, u32 msix_vec)
{
	struct packet_msg_prot *cq_pkt;
	u32 tmp;

	cq_pkt = (struct packet_msg_prot *) (uintptr_t)
		(kernel_address + len - (sizeof(struct packet_msg_prot) * 2));

	tmp = (PACKET_MSG_PROT << GOYA_PKT_CTL_OPCODE_SHIFT) |
			(1 << GOYA_PKT_CTL_EB_SHIFT) |
			(1 << GOYA_PKT_CTL_MB_SHIFT);
	cq_pkt->ctl = cpu_to_le32(tmp);
	cq_pkt->value = cpu_to_le32(cq_val);
	cq_pkt->addr = cpu_to_le64(cq_addr);

	cq_pkt++;

	tmp = (PACKET_MSG_PROT << GOYA_PKT_CTL_OPCODE_SHIFT) |
			(1 << GOYA_PKT_CTL_MB_SHIFT);
	cq_pkt->ctl = cpu_to_le32(tmp);
	cq_pkt->value = cpu_to_le32(msix_vec & 0x7FF);
	cq_pkt->addr = cpu_to_le64(CFG_BASE + mmPCIE_DBI_MSIX_DOORBELL_OFF);
}