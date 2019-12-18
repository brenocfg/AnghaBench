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
struct ocrdma_dev {int dummy; } ;
struct ib_pma_portcounters {void* port_rcv_packets; void* port_xmit_packets; void* port_rcv_data; void* port_xmit_data; } ;
struct ib_mad {scalar_t__ data; } ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_sysfs_rcv_data (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_sysfs_rcv_pkts (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_sysfs_xmit_data (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_sysfs_xmit_pkts (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_update_stats (struct ocrdma_dev*) ; 

int ocrdma_pma_counters(struct ocrdma_dev *dev,
			struct ib_mad *out_mad)
{
	struct ib_pma_portcounters *pma_cnt;

	memset(out_mad->data, 0, sizeof out_mad->data);
	pma_cnt = (void *)(out_mad->data + 40);
	ocrdma_update_stats(dev);

	pma_cnt->port_xmit_data    = cpu_to_be32(ocrdma_sysfs_xmit_data(dev));
	pma_cnt->port_rcv_data     = cpu_to_be32(ocrdma_sysfs_rcv_data(dev));
	pma_cnt->port_xmit_packets = cpu_to_be32(ocrdma_sysfs_xmit_pkts(dev));
	pma_cnt->port_rcv_packets  = cpu_to_be32(ocrdma_sysfs_rcv_pkts(dev));
	return 0;
}