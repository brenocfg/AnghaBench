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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {scalar_t__ sleep_cookie_vbase; TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {int /*<<< orphan*/  sleep_cookie; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 scalar_t__ FW_AWAKE_COOKIE ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static bool mwifiex_pcie_ok_to_access_hw(struct mwifiex_adapter *adapter)
{
	u32 cookie_value;
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	if (!reg->sleep_cookie)
		return true;

	if (card->sleep_cookie_vbase) {
		cookie_value = get_unaligned_le32(card->sleep_cookie_vbase);
		mwifiex_dbg(adapter, INFO,
			    "info: ACCESS_HW: sleep cookie=0x%x\n",
			    cookie_value);
		if (cookie_value == FW_AWAKE_COOKIE)
			return true;
	}

	return false;
}