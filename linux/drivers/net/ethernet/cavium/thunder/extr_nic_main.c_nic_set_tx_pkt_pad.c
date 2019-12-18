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
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct nicpf {TYPE_1__* hw; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int bgx_cnt; } ;

/* Variables and functions */
 int MAX_LMAC_PER_BGX ; 
 int NIC_PF_LMAC_0_7_CFG ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 scalar_t__ PCI_SUBSYS_DEVID_81XX_NIC_PF ; 
 int nic_reg_read (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void nic_set_tx_pkt_pad(struct nicpf *nic, int size)
{
	int lmac, max_lmac;
	u16 sdevid;
	u64 lmac_cfg;

	/* There is a issue in HW where-in while sending GSO sized
	 * pkts as part of TSO, if pkt len falls below this size
	 * NIC will zero PAD packet and also updates IP total length.
	 * Hence set this value to lessthan min pkt size of MAC+IP+TCP
	 * headers, BGX will do the padding to transmit 64 byte pkt.
	 */
	if (size > 52)
		size = 52;

	pci_read_config_word(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);
	/* 81xx's RGX has only one LMAC */
	if (sdevid == PCI_SUBSYS_DEVID_81XX_NIC_PF)
		max_lmac = ((nic->hw->bgx_cnt - 1) * MAX_LMAC_PER_BGX) + 1;
	else
		max_lmac = nic->hw->bgx_cnt * MAX_LMAC_PER_BGX;

	for (lmac = 0; lmac < max_lmac; lmac++) {
		lmac_cfg = nic_reg_read(nic, NIC_PF_LMAC_0_7_CFG | (lmac << 3));
		lmac_cfg &= ~(0xF << 2);
		lmac_cfg |= ((size / 4) << 2);
		nic_reg_write(nic, NIC_PF_LMAC_0_7_CFG | (lmac << 3), lmac_cfg);
	}
}