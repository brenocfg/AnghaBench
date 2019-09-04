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
typedef  unsigned long long u64 ;
struct nicvf {int sqs_count; struct nicvf** snicvf; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  NIC_QSET_RQ_GEN_CFG ; 
 unsigned long long nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

void nicvf_config_vlan_stripping(struct nicvf *nic, netdev_features_t features)
{
	u64 rq_cfg;
	int sqs;

	rq_cfg = nicvf_queue_reg_read(nic, NIC_QSET_RQ_GEN_CFG, 0);

	/* Enable first VLAN stripping */
	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		rq_cfg |= (1ULL << 25);
	else
		rq_cfg &= ~(1ULL << 25);
	nicvf_queue_reg_write(nic, NIC_QSET_RQ_GEN_CFG, 0, rq_cfg);

	/* Configure Secondary Qsets, if any */
	for (sqs = 0; sqs < nic->sqs_count; sqs++)
		if (nic->snicvf[sqs])
			nicvf_queue_reg_write(nic->snicvf[sqs],
					      NIC_QSET_RQ_GEN_CFG, 0, rq_cfg);
}