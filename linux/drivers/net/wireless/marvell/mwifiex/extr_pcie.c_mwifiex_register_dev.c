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
struct TYPE_2__ {int /*<<< orphan*/  can_ext_scan; int /*<<< orphan*/  num_mem_types; int /*<<< orphan*/  mem_type_mapping_tbl; int /*<<< orphan*/  tx_buf_size; } ;
struct pcie_service_card {TYPE_1__ pcie; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int /*<<< orphan*/  ext_scan; int /*<<< orphan*/  num_mem_types; int /*<<< orphan*/  mem_type_mapping_tbl; int /*<<< orphan*/  tx_buf_size; struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_pcie_get_fw_name (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_pcie_request_irq (struct mwifiex_adapter*) ; 

__attribute__((used)) static int mwifiex_register_dev(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;

	/* save adapter pointer in card */
	card->adapter = adapter;

	if (mwifiex_pcie_request_irq(adapter))
		return -1;

	adapter->tx_buf_size = card->pcie.tx_buf_size;
	adapter->mem_type_mapping_tbl = card->pcie.mem_type_mapping_tbl;
	adapter->num_mem_types = card->pcie.num_mem_types;
	adapter->ext_scan = card->pcie.can_ext_scan;
	mwifiex_pcie_get_fw_name(adapter);

	return 0;
}