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
typedef  size_t u8 ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int src_nentries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_PCI ; 
 int /*<<< orphan*/  ath10k_ce_per_engine_service (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_pci_hif_get_free_queue_number (struct ath10k*,size_t) ; 
 TYPE_1__* host_ce_config_wlan ; 

void ath10k_pci_hif_send_complete_check(struct ath10k *ar, u8 pipe,
					int force)
{
	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci hif send complete check\n");

	if (!force) {
		int resources;
		/*
		 * Decide whether to actually poll for completions, or just
		 * wait for a later chance.
		 * If there seem to be plenty of resources left, then just wait
		 * since checking involves reading a CE register, which is a
		 * relatively expensive operation.
		 */
		resources = ath10k_pci_hif_get_free_queue_number(ar, pipe);

		/*
		 * If at least 50% of the total resources are still available,
		 * don't bother checking again yet.
		 */
		if (resources > (host_ce_config_wlan[pipe].src_nentries >> 1))
			return;
	}
	ath10k_ce_per_engine_service(ar, pipe);
}