#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_4__ {TYPE_1__* pdev_param; } ;
struct ath10k {scalar_t__ state; TYPE_2__ wmi; void* cfg_rx_chainmask; void* cfg_tx_chainmask; int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_chain_mask; int /*<<< orphan*/  tx_chain_mask; } ;

/* Variables and functions */
 scalar_t__ ATH10K_STATE_ON ; 
 scalar_t__ ATH10K_STATE_RESTARTED ; 
 int /*<<< orphan*/  ath10k_check_chain_mask (struct ath10k*,void*,char*) ; 
 int /*<<< orphan*/  ath10k_mac_setup_ht_vht_cap (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,void*) ; 
 int ath10k_wmi_pdev_set_param (struct ath10k*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ath10k_set_antenna(struct ath10k *ar, u32 tx_ant, u32 rx_ant)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath10k_check_chain_mask(ar, tx_ant, "tx");
	ath10k_check_chain_mask(ar, rx_ant, "rx");

	ar->cfg_tx_chainmask = tx_ant;
	ar->cfg_rx_chainmask = rx_ant;

	if ((ar->state != ATH10K_STATE_ON) &&
	    (ar->state != ATH10K_STATE_RESTARTED))
		return 0;

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->tx_chain_mask,
					tx_ant);
	if (ret) {
		ath10k_warn(ar, "failed to set tx-chainmask: %d, req 0x%x\n",
			    ret, tx_ant);
		return ret;
	}

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->rx_chain_mask,
					rx_ant);
	if (ret) {
		ath10k_warn(ar, "failed to set rx-chainmask: %d, req 0x%x\n",
			    ret, rx_ant);
		return ret;
	}

	/* Reload HT/VHT capability */
	ath10k_mac_setup_ht_vht_cap(ar);

	return 0;
}