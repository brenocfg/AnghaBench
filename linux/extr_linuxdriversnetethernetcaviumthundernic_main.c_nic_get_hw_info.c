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
typedef  int u16 ;
struct nicpf {int /*<<< orphan*/  pdev; struct hw_info* hw; } ;
struct hw_info {int chans_per_lmac; int chans_per_bgx; int cpi_cnt; int rssi_cnt; int rss_ind_tbl_size; int tl3_cnt; int tl2_cnt; int tl1_cnt; int tl1_per_bgx; int chans_per_rgx; int chans_per_lbk; int tl4_cnt; int /*<<< orphan*/  bgx_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_BGX_PER_CN81XX ; 
 int /*<<< orphan*/  MAX_BGX_PER_CN83XX ; 
 int /*<<< orphan*/  MAX_BGX_PER_CN88XX ; 
 int MAX_QUEUES_PER_QSET ; 
 int NIC_MAX_RSS_IDR_TBL_SIZE ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
#define  PCI_SUBSYS_DEVID_81XX_NIC_PF 130 
#define  PCI_SUBSYS_DEVID_83XX_NIC_PF 129 
#define  PCI_SUBSYS_DEVID_88XX_NIC_PF 128 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_sriov_get_totalvfs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nic_get_hw_info(struct nicpf *nic)
{
	u16 sdevid;
	struct hw_info *hw = nic->hw;

	pci_read_config_word(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);

	switch (sdevid) {
	case PCI_SUBSYS_DEVID_88XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PER_CN88XX;
		hw->chans_per_lmac = 16;
		hw->chans_per_bgx = 128;
		hw->cpi_cnt = 2048;
		hw->rssi_cnt = 4096;
		hw->rss_ind_tbl_size = NIC_MAX_RSS_IDR_TBL_SIZE;
		hw->tl3_cnt = 256;
		hw->tl2_cnt = 64;
		hw->tl1_cnt = 2;
		hw->tl1_per_bgx = true;
		break;
	case PCI_SUBSYS_DEVID_81XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PER_CN81XX;
		hw->chans_per_lmac = 8;
		hw->chans_per_bgx = 32;
		hw->chans_per_rgx = 8;
		hw->chans_per_lbk = 24;
		hw->cpi_cnt = 512;
		hw->rssi_cnt = 256;
		hw->rss_ind_tbl_size = 32; /* Max RSSI / Max interfaces */
		hw->tl3_cnt = 64;
		hw->tl2_cnt = 16;
		hw->tl1_cnt = 10;
		hw->tl1_per_bgx = false;
		break;
	case PCI_SUBSYS_DEVID_83XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PER_CN83XX;
		hw->chans_per_lmac = 8;
		hw->chans_per_bgx = 32;
		hw->chans_per_lbk = 64;
		hw->cpi_cnt = 2048;
		hw->rssi_cnt = 1024;
		hw->rss_ind_tbl_size = 64; /* Max RSSI / Max interfaces */
		hw->tl3_cnt = 256;
		hw->tl2_cnt = 64;
		hw->tl1_cnt = 18;
		hw->tl1_per_bgx = false;
		break;
	}
	hw->tl4_cnt = MAX_QUEUES_PER_QSET * pci_sriov_get_totalvfs(nic->pdev);
}