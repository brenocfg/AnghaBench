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
struct TYPE_2__ {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ rss_size; } ;
struct nicvf {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_RSS_SIZE ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_get_rss_size(struct nicvf *nic)
{
	union nic_mbx mbx = {};

	mbx.rss_size.msg = NIC_MBOX_MSG_RSS_SIZE;
	mbx.rss_size.vf_id = nic->vf_id;
	nicvf_send_msg_to_pf(nic, &mbx);
}