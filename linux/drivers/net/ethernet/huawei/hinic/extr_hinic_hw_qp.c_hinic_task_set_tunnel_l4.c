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
struct hinic_sq_task {int pkt_info2; } ;
typedef  enum hinic_l4_tunnel_type { ____Placeholder_hinic_l4_tunnel_type } hinic_l4_tunnel_type ;

/* Variables and functions */
 int HINIC_SQ_TASK_INFO2_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNNEL_L4LEN ; 
 int /*<<< orphan*/  TUNNEL_L4TYPE ; 

void hinic_task_set_tunnel_l4(struct hinic_sq_task *task,
			      enum hinic_l4_tunnel_type l4_type,
			      u32 tunnel_len)
{
	task->pkt_info2 |= HINIC_SQ_TASK_INFO2_SET(l4_type, TUNNEL_L4TYPE) |
			   HINIC_SQ_TASK_INFO2_SET(tunnel_len, TUNNEL_L4LEN);
}