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
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {scalar_t__ sleep_cookie; int /*<<< orphan*/  fw_status; } ;
struct mwifiex_adapter {int /*<<< orphan*/  ps_state; struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  FIRMWARE_READY_PCIE ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  PS_STATE_AWAKE ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_pcie_dev_wakeup_delay (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pm_wakeup_card(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	mwifiex_dbg(adapter, EVENT,
		    "event: Wakeup device...\n");

	if (reg->sleep_cookie)
		mwifiex_pcie_dev_wakeup_delay(adapter);

	/* Accessing fw_status register will wakeup device */
	if (mwifiex_write_reg(adapter, reg->fw_status, FIRMWARE_READY_PCIE)) {
		mwifiex_dbg(adapter, ERROR,
			    "Writing fw_status register failed\n");
		return -1;
	}

	if (reg->sleep_cookie) {
		mwifiex_pcie_dev_wakeup_delay(adapter);
		mwifiex_dbg(adapter, INFO,
			    "PCIE wakeup: Setting PS_STATE_AWAKE\n");
		adapter->ps_state = PS_STATE_AWAKE;
	}

	return 0;
}