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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_service_card {int /*<<< orphan*/ * sleep_cookie_vbase; int /*<<< orphan*/  sleep_cookie_pbase; int /*<<< orphan*/  dev; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pcie_delete_sleep_cookie_buf(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card;

	if (!adapter)
		return 0;

	card = adapter->card;

	if (card && card->sleep_cookie_vbase) {
		pci_free_consistent(card->dev, sizeof(u32),
				    card->sleep_cookie_vbase,
				    card->sleep_cookie_pbase);
		card->sleep_cookie_vbase = NULL;
	}

	return 0;
}