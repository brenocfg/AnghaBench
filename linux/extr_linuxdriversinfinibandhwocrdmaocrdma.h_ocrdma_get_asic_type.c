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
typedef  int u8 ;
struct TYPE_2__ {int dev_family; int /*<<< orphan*/  pdev; } ;
struct ocrdma_dev {int asic_id; TYPE_1__ nic_info; } ;

/* Variables and functions */
 int OCRDMA_SLI_ASIC_GEN_NUM_MASK ; 
 int OCRDMA_SLI_ASIC_GEN_NUM_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_SLI_ASIC_ID_OFFSET ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline u8 ocrdma_get_asic_type(struct ocrdma_dev *dev)
{
	if (dev->nic_info.dev_family == 0xF && !dev->asic_id) {
		pci_read_config_dword(
			dev->nic_info.pdev,
			OCRDMA_SLI_ASIC_ID_OFFSET, &dev->asic_id);
	}

	return (dev->asic_id & OCRDMA_SLI_ASIC_GEN_NUM_MASK) >>
				OCRDMA_SLI_ASIC_GEN_NUM_SHIFT;
}