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
struct reset_stat_cfg {int rx_stat_mask; int tx_stat_mask; int rq_stat_mask; int sq_stat_mask; } ;
struct nicpf {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int NIC_PF_QSET_0_127_RQ_0_7_STAT_0_1 ; 
 int NIC_PF_QSET_0_127_SQ_0_7_STAT_0_1 ; 
 int NIC_PF_VNIC_0_127_RX_STAT_0_13 ; 
 int NIC_PF_VNIC_0_127_TX_STAT_0_4 ; 
 int NIC_QS_ID_SHIFT ; 
 int NIC_Q_NUM_SHIFT ; 
 int RX_STATS_ENUM_LAST ; 
 int TX_STATS_ENUM_LAST ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nic_reset_stat_counters(struct nicpf *nic,
				   int vf, struct reset_stat_cfg *cfg)
{
	int i, stat, qnum;
	u64 reg_addr;

	for (i = 0; i < RX_STATS_ENUM_LAST; i++) {
		if (cfg->rx_stat_mask & BIT(i)) {
			reg_addr = NIC_PF_VNIC_0_127_RX_STAT_0_13 |
				   (vf << NIC_QS_ID_SHIFT) |
				   (i << 3);
			nic_reg_write(nic, reg_addr, 0);
		}
	}

	for (i = 0; i < TX_STATS_ENUM_LAST; i++) {
		if (cfg->tx_stat_mask & BIT(i)) {
			reg_addr = NIC_PF_VNIC_0_127_TX_STAT_0_4 |
				   (vf << NIC_QS_ID_SHIFT) |
				   (i << 3);
			nic_reg_write(nic, reg_addr, 0);
		}
	}

	for (i = 0; i <= 15; i++) {
		qnum = i >> 1;
		stat = i & 1 ? 1 : 0;
		reg_addr = (vf << NIC_QS_ID_SHIFT) |
			   (qnum << NIC_Q_NUM_SHIFT) | (stat << 3);
		if (cfg->rq_stat_mask & BIT(i)) {
			reg_addr |= NIC_PF_QSET_0_127_RQ_0_7_STAT_0_1;
			nic_reg_write(nic, reg_addr, 0);
		}
		if (cfg->sq_stat_mask & BIT(i)) {
			reg_addr |= NIC_PF_QSET_0_127_SQ_0_7_STAT_0_1;
			nic_reg_write(nic, reg_addr, 0);
		}
	}

	return 0;
}