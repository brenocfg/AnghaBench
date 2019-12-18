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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct bnxt {int /*<<< orphan*/  dev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_DSN ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_pcie_dsn_get(struct bnxt *bp, u8 dsn[])
{
	struct pci_dev *pdev = bp->pdev;
	int pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_DSN);
	u32 dw;

	if (!pos) {
		netdev_info(bp->dev, "Unable do read adapter's DSN");
		return -EOPNOTSUPP;
	}

	/* DSN (two dw) is at an offset of 4 from the cap pos */
	pos += 4;
	pci_read_config_dword(pdev, pos, &dw);
	put_unaligned_le32(dw, &dsn[0]);
	pci_read_config_dword(pdev, pos + 4, &dw);
	put_unaligned_le32(dw, &dsn[4]);
	return 0;
}