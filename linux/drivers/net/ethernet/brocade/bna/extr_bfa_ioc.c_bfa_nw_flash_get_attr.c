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
typedef  int /*<<< orphan*/  u8 ;
struct bfi_flash_query_req {int /*<<< orphan*/  alen; int /*<<< orphan*/  mh; } ;
struct bfa_flash_attr {int dummy; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_flash {int op_busy; TYPE_1__ mb; int /*<<< orphan*/  ioc; int /*<<< orphan*/  dbuf_pa; int /*<<< orphan*/ * ubuf; void* cbarg; int /*<<< orphan*/  cbfn; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;
typedef  int /*<<< orphan*/  bfa_cb_flash ;

/* Variables and functions */
 int BFA_STATUS_DEVBUSY ; 
 int BFA_STATUS_IOC_NON_OP ; 
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFI_FLASH_H2I_QUERY_REQ ; 
 int /*<<< orphan*/  BFI_MC_FLASH ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_is_operational (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum bfa_status
bfa_nw_flash_get_attr(struct bfa_flash *flash, struct bfa_flash_attr *attr,
		      bfa_cb_flash cbfn, void *cbarg)
{
	struct bfi_flash_query_req *msg =
			(struct bfi_flash_query_req *) flash->mb.msg;

	if (!bfa_nw_ioc_is_operational(flash->ioc))
		return BFA_STATUS_IOC_NON_OP;

	if (flash->op_busy)
		return BFA_STATUS_DEVBUSY;

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->ubuf = (u8 *) attr;

	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_QUERY_REQ,
		    bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, sizeof(struct bfa_flash_attr), flash->dbuf_pa);
	bfa_nw_ioc_mbox_queue(flash->ioc, &flash->mb, NULL, NULL);

	return BFA_STATUS_OK;
}