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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mlxsw_pci {struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_address_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_byte_count_set (char*,int,size_t) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,char*,size_t,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_pci_wqe_frag_map(struct mlxsw_pci *mlxsw_pci, char *wqe,
				  int index, char *frag_data, size_t frag_len,
				  int direction)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;
	dma_addr_t mapaddr;

	mapaddr = pci_map_single(pdev, frag_data, frag_len, direction);
	if (unlikely(pci_dma_mapping_error(pdev, mapaddr))) {
		dev_err_ratelimited(&pdev->dev, "failed to dma map tx frag\n");
		return -EIO;
	}
	mlxsw_pci_wqe_address_set(wqe, index, mapaddr);
	mlxsw_pci_wqe_byte_count_set(wqe, index, frag_len);
	return 0;
}