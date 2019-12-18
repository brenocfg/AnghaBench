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
struct hinic_sq_task {int /*<<< orphan*/  pkt_info1; int /*<<< orphan*/  pkt_info0; } ;
typedef  enum hinic_l4_offload_type { ____Placeholder_hinic_l4_offload_type } hinic_l4_offload_type ;

/* Variables and functions */
 int HINIC_MSS_DEFAULT ; 
 int HINIC_SQ_CTRL_CLEAR (int,int /*<<< orphan*/ ) ; 
 int HINIC_SQ_CTRL_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO0_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO1_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INNER_L4LEN ; 
 int /*<<< orphan*/  L4_OFFLOAD ; 
 int /*<<< orphan*/  QUEUE_INFO_MSS ; 
 int /*<<< orphan*/  QUEUE_INFO_PLDOFF ; 
 int /*<<< orphan*/  QUEUE_INFO_SCTP ; 
 int /*<<< orphan*/  QUEUE_INFO_TCPUDP_CS ; 
 int SCTP_OFFLOAD_ENABLE ; 
 int TCP_OFFLOAD_ENABLE ; 
 int UDP_OFFLOAD_ENABLE ; 

void hinic_set_cs_inner_l4(struct hinic_sq_task *task, u32 *queue_info,
			   enum hinic_l4_offload_type l4_offload,
			   u32 l4_len, u32 offset)
{
	u32 tcp_udp_cs = 0, sctp = 0;
	u32 mss = HINIC_MSS_DEFAULT;

	if (l4_offload == TCP_OFFLOAD_ENABLE ||
	    l4_offload == UDP_OFFLOAD_ENABLE)
		tcp_udp_cs = 1;
	else if (l4_offload == SCTP_OFFLOAD_ENABLE)
		sctp = 1;

	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(l4_offload, L4_OFFLOAD);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(l4_len, INNER_L4LEN);

	*queue_info |= HINIC_SQ_CTRL_SET(offset, QUEUE_INFO_PLDOFF) |
		       HINIC_SQ_CTRL_SET(tcp_udp_cs, QUEUE_INFO_TCPUDP_CS) |
		       HINIC_SQ_CTRL_SET(sctp, QUEUE_INFO_SCTP);

	*queue_info = HINIC_SQ_CTRL_CLEAR(*queue_info, QUEUE_INFO_MSS);
	*queue_info |= HINIC_SQ_CTRL_SET(mss, QUEUE_INFO_MSS);
}