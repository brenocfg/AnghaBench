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
struct TYPE_2__ {int mode; void* msg; scalar_t__ mac; } ;
union nic_mbx {TYPE_1__ xcast; } ;
typedef  int u8 ;
struct xcast_addr_list {int count; scalar_t__* mc; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int BGX_XCAST_MCAST_FILTER ; 
 void* NIC_MBOX_MSG_ADD_MCAST ; 
 void* NIC_MBOX_MSG_RESET_XCAST ; 
 void* NIC_MBOX_MSG_SET_XCAST ; 
 int /*<<< orphan*/  kfree (struct xcast_addr_list*) ; 
 scalar_t__ nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void __nicvf_set_rx_mode_task(u8 mode, struct xcast_addr_list *mc_addrs,
				     struct nicvf *nic)
{
	union nic_mbx mbx = {};
	int idx;

	/* From the inside of VM code flow we have only 128 bits memory
	 * available to send message to host's PF, so send all mc addrs
	 * one by one, starting from flush command in case if kernel
	 * requests to configure specific MAC filtering
	 */

	/* flush DMAC filters and reset RX mode */
	mbx.xcast.msg = NIC_MBOX_MSG_RESET_XCAST;
	if (nicvf_send_msg_to_pf(nic, &mbx) < 0)
		goto free_mc;

	if (mode & BGX_XCAST_MCAST_FILTER) {
		/* once enabling filtering, we need to signal to PF to add
		 * its' own LMAC to the filter to accept packets for it.
		 */
		mbx.xcast.msg = NIC_MBOX_MSG_ADD_MCAST;
		mbx.xcast.mac = 0;
		if (nicvf_send_msg_to_pf(nic, &mbx) < 0)
			goto free_mc;
	}

	/* check if we have any specific MACs to be added to PF DMAC filter */
	if (mc_addrs) {
		/* now go through kernel list of MACs and add them one by one */
		for (idx = 0; idx < mc_addrs->count; idx++) {
			mbx.xcast.msg = NIC_MBOX_MSG_ADD_MCAST;
			mbx.xcast.mac = mc_addrs->mc[idx];
			if (nicvf_send_msg_to_pf(nic, &mbx) < 0)
				goto free_mc;
		}
	}

	/* and finally set rx mode for PF accordingly */
	mbx.xcast.msg = NIC_MBOX_MSG_SET_XCAST;
	mbx.xcast.mode = mode;

	nicvf_send_msg_to_pf(nic, &mbx);
free_mc:
	kfree(mc_addrs);
}