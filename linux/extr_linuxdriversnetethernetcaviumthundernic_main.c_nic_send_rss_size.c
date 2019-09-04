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
struct TYPE_3__ {int /*<<< orphan*/  ind_tbl_size; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ rss_size; } ;
struct nicpf {TYPE_2__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  rss_ind_tbl_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_RSS_SIZE ; 
 int /*<<< orphan*/  nic_send_msg_to_vf (struct nicpf*,int,union nic_mbx*) ; 

__attribute__((used)) static void nic_send_rss_size(struct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};

	mbx.rss_size.msg = NIC_MBOX_MSG_RSS_SIZE;
	mbx.rss_size.ind_tbl_size = nic->hw->rss_ind_tbl_size;
	nic_send_msg_to_vf(nic, vf, &mbx);
}