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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdio_func {int dummy; } ;
struct sdio_data {struct sdio_func* func; } ;
struct intf_hdl {struct dvobj_priv* pintf_dev; struct adapter* padapter; } ;
struct dvobj_priv {struct sdio_data intf_data; } ;
struct adapter {scalar_t__ bSurpriseRemoved; } ;
typedef  int s32 ;

/* Variables and functions */
 int _sd_cmd52_read (struct intf_hdl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rtw_sdio_claim_host_needed (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

s32 sd_cmd52_read(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *pdata)
{
	struct adapter *padapter;
	struct dvobj_priv *psdiodev;
	struct sdio_data *psdio;

	int err = 0;
	struct sdio_func *func;
	bool claim_needed;

	padapter = pintfhdl->padapter;
	psdiodev = pintfhdl->pintf_dev;
	psdio = &psdiodev->intf_data;

	if (padapter->bSurpriseRemoved) {
		/* DBG_871X(" %s (padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n", __func__); */
		return err;
	}

	func = psdio->func;
	claim_needed = rtw_sdio_claim_host_needed(func);

	if (claim_needed)
		sdio_claim_host(func);
	err = _sd_cmd52_read(pintfhdl, addr, cnt, pdata);
	if (claim_needed)
		sdio_release_host(func);
	return err;
}