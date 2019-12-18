#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lan743x_csr {int id_rev; int /*<<< orphan*/  flags; void* fpga_rev; int /*<<< orphan*/  csr_address; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct lan743x_csr csr; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FPGA_REV ; 
 int /*<<< orphan*/  FPGA_REV_GET_MAJOR_ (void*) ; 
 int /*<<< orphan*/  FPGA_REV_GET_MINOR_ (void*) ; 
 int /*<<< orphan*/  ID_REV ; 
#define  ID_REV_CHIP_REV_A0_ 129 
#define  ID_REV_CHIP_REV_B0_ 128 
 int ID_REV_CHIP_REV_MASK_ ; 
 int /*<<< orphan*/  ID_REV_IS_VALID_CHIP_ID_ (int) ; 
 int /*<<< orphan*/  LAN743X_CSR_FLAG_IS_A0 ; 
 int /*<<< orphan*/  LAN743X_CSR_FLAG_IS_B0 ; 
 int /*<<< orphan*/  LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lan743x_csr_light_reset (struct lan743x_adapter*) ; 
 void* lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int lan743x_csr_init(struct lan743x_adapter *adapter)
{
	struct lan743x_csr *csr = &adapter->csr;
	resource_size_t bar_start, bar_length;
	int result;

	bar_start = pci_resource_start(adapter->pdev, 0);
	bar_length = pci_resource_len(adapter->pdev, 0);
	csr->csr_address = devm_ioremap(&adapter->pdev->dev,
					bar_start, bar_length);
	if (!csr->csr_address) {
		result = -ENOMEM;
		goto clean_up;
	}

	csr->id_rev = lan743x_csr_read(adapter, ID_REV);
	csr->fpga_rev = lan743x_csr_read(adapter, FPGA_REV);
	netif_info(adapter, probe, adapter->netdev,
		   "ID_REV = 0x%08X, FPGA_REV = %d.%d\n",
		   csr->id_rev,	FPGA_REV_GET_MAJOR_(csr->fpga_rev),
		   FPGA_REV_GET_MINOR_(csr->fpga_rev));
	if (!ID_REV_IS_VALID_CHIP_ID_(csr->id_rev)) {
		result = -ENODEV;
		goto clean_up;
	}

	csr->flags = LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR;
	switch (csr->id_rev & ID_REV_CHIP_REV_MASK_) {
	case ID_REV_CHIP_REV_A0_:
		csr->flags |= LAN743X_CSR_FLAG_IS_A0;
		csr->flags &= ~LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR;
		break;
	case ID_REV_CHIP_REV_B0_:
		csr->flags |= LAN743X_CSR_FLAG_IS_B0;
		break;
	}

	result = lan743x_csr_light_reset(adapter);
	if (result)
		goto clean_up;
	return 0;
clean_up:
	return result;
}