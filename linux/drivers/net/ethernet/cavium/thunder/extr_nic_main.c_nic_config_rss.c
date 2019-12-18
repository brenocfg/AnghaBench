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
typedef  size_t u8 ;
typedef  int u64 ;
struct rss_cfg_msg {size_t vf_id; int tbl_offset; int tbl_len; int* ind_tbl; int hash_bits; } ;
struct nicpf {int* rssi_base; size_t** vf_sqs; int* cpi_base; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int NIC_PF_CPI_0_2047_CFG ; 
 int NIC_PF_MPI_0_2047_CFG ; 
 int NIC_PF_RSSI_0_4097_RQ ; 
 int nic_reg_read (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 
 scalar_t__ pass1_silicon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nic_config_rss(struct nicpf *nic, struct rss_cfg_msg *cfg)
{
	u8  qset, idx = 0;
	u64 cpi_cfg, cpi_base, rssi_base, rssi;
	u64 idx_addr;

	rssi_base = nic->rssi_base[cfg->vf_id] + cfg->tbl_offset;

	rssi = rssi_base;

	for (; rssi < (rssi_base + cfg->tbl_len); rssi++) {
		u8 svf = cfg->ind_tbl[idx] >> 3;

		if (svf)
			qset = nic->vf_sqs[cfg->vf_id][svf - 1];
		else
			qset = cfg->vf_id;
		nic_reg_write(nic, NIC_PF_RSSI_0_4097_RQ | (rssi << 3),
			      (qset << 3) | (cfg->ind_tbl[idx] & 0x7));
		idx++;
	}

	cpi_base = nic->cpi_base[cfg->vf_id];
	if (pass1_silicon(nic->pdev))
		idx_addr = NIC_PF_CPI_0_2047_CFG;
	else
		idx_addr = NIC_PF_MPI_0_2047_CFG;
	cpi_cfg = nic_reg_read(nic, idx_addr | (cpi_base << 3));
	cpi_cfg &= ~(0xFULL << 20);
	cpi_cfg |= (cfg->hash_bits << 20);
	nic_reg_write(nic, idx_addr | (cpi_base << 3), cpi_cfg);
}