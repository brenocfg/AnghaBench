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
struct pci_dev {int dummy; } ;
struct amd8131_dev_info {struct pci_dev* dev; } ;

/* Variables and functions */
 int INT_CTLR_DTS ; 
 int INT_CTLR_DTSE ; 
 int INT_CTLR_PERR ; 
 int INT_CTLR_SERR ; 
 int LNK_CTRL_CRCERR_A ; 
 int LNK_CTRL_CRCERR_B ; 
 int LNK_CTRL_CRCFEN ; 
 int MEM_LIMIT_MASK ; 
 int /*<<< orphan*/  REG_INT_CTLR ; 
 int /*<<< orphan*/  REG_LNK_CTRL_A ; 
 int /*<<< orphan*/  REG_LNK_CTRL_B ; 
 int /*<<< orphan*/  REG_MEM_LIM ; 
 int /*<<< orphan*/  REG_STS_CMD ; 
 int STS_CMD_SERREN ; 
 int /*<<< orphan*/  edac_pci_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  edac_pci_write_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amd8131_pcix_init(struct amd8131_dev_info *dev_info)
{
	u32 val32;
	struct pci_dev *dev = dev_info->dev;

	/* First clear error detection flags */
	edac_pci_read_dword(dev, REG_MEM_LIM, &val32);
	if (val32 & MEM_LIMIT_MASK)
		edac_pci_write_dword(dev, REG_MEM_LIM, val32);

	/* Clear Discard Timer Timedout flag */
	edac_pci_read_dword(dev, REG_INT_CTLR, &val32);
	if (val32 & INT_CTLR_DTS)
		edac_pci_write_dword(dev, REG_INT_CTLR, val32);

	/* Clear CRC Error flag on link side A */
	edac_pci_read_dword(dev, REG_LNK_CTRL_A, &val32);
	if (val32 & LNK_CTRL_CRCERR_A)
		edac_pci_write_dword(dev, REG_LNK_CTRL_A, val32);

	/* Clear CRC Error flag on link side B */
	edac_pci_read_dword(dev, REG_LNK_CTRL_B, &val32);
	if (val32 & LNK_CTRL_CRCERR_B)
		edac_pci_write_dword(dev, REG_LNK_CTRL_B, val32);

	/*
	 * Then enable all error detections.
	 *
	 * Setup Discard Timer Sync Flood Enable,
	 * System Error Enable and Parity Error Enable.
	 */
	edac_pci_read_dword(dev, REG_INT_CTLR, &val32);
	val32 |= INT_CTLR_PERR | INT_CTLR_SERR | INT_CTLR_DTSE;
	edac_pci_write_dword(dev, REG_INT_CTLR, val32);

	/* Enable overall SERR Error detection */
	edac_pci_read_dword(dev, REG_STS_CMD, &val32);
	val32 |= STS_CMD_SERREN;
	edac_pci_write_dword(dev, REG_STS_CMD, val32);

	/* Setup CRC Flood Enable for link side A */
	edac_pci_read_dword(dev, REG_LNK_CTRL_A, &val32);
	val32 |= LNK_CTRL_CRCFEN;
	edac_pci_write_dword(dev, REG_LNK_CTRL_A, val32);

	/* Setup CRC Flood Enable for link side B */
	edac_pci_read_dword(dev, REG_LNK_CTRL_B, &val32);
	val32 |= LNK_CTRL_CRCFEN;
	edac_pci_write_dword(dev, REG_LNK_CTRL_B, val32);
}