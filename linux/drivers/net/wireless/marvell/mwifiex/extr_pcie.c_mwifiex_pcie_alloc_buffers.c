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
struct pcie_service_card {int /*<<< orphan*/ * sleep_cookie_vbase; int /*<<< orphan*/ * cmdrsp_buf; TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {scalar_t__ sleep_cookie; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_pcie_alloc_cmdrsp_buf (struct mwifiex_adapter*) ; 
 int mwifiex_pcie_alloc_sleep_cookie_buf (struct mwifiex_adapter*) ; 
 int mwifiex_pcie_create_evtbd_ring (struct mwifiex_adapter*) ; 
 int mwifiex_pcie_create_rxbd_ring (struct mwifiex_adapter*) ; 
 int mwifiex_pcie_create_txbd_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_cmdrsp_buf (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_evtbd_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_rxbd_ring (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_pcie_delete_txbd_ring (struct mwifiex_adapter*) ; 

__attribute__((used)) static int mwifiex_pcie_alloc_buffers(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	int ret;

	card->cmdrsp_buf = NULL;
	ret = mwifiex_pcie_create_txbd_ring(adapter);
	if (ret) {
		mwifiex_dbg(adapter, ERROR, "Failed to create txbd ring\n");
		goto err_cre_txbd;
	}

	ret = mwifiex_pcie_create_rxbd_ring(adapter);
	if (ret) {
		mwifiex_dbg(adapter, ERROR, "Failed to create rxbd ring\n");
		goto err_cre_rxbd;
	}

	ret = mwifiex_pcie_create_evtbd_ring(adapter);
	if (ret) {
		mwifiex_dbg(adapter, ERROR, "Failed to create evtbd ring\n");
		goto err_cre_evtbd;
	}

	ret = mwifiex_pcie_alloc_cmdrsp_buf(adapter);
	if (ret) {
		mwifiex_dbg(adapter, ERROR, "Failed to allocate cmdbuf buffer\n");
		goto err_alloc_cmdbuf;
	}

	if (reg->sleep_cookie) {
		ret = mwifiex_pcie_alloc_sleep_cookie_buf(adapter);
		if (ret) {
			mwifiex_dbg(adapter, ERROR, "Failed to allocate sleep_cookie buffer\n");
			goto err_alloc_cookie;
		}
	} else {
		card->sleep_cookie_vbase = NULL;
	}

	return 0;

err_alloc_cookie:
	mwifiex_pcie_delete_cmdrsp_buf(adapter);
err_alloc_cmdbuf:
	mwifiex_pcie_delete_evtbd_ring(adapter);
err_cre_evtbd:
	mwifiex_pcie_delete_rxbd_ring(adapter);
err_cre_rxbd:
	mwifiex_pcie_delete_txbd_ring(adapter);
err_cre_txbd:
	return ret;
}