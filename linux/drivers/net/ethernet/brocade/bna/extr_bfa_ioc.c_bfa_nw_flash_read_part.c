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
typedef  int u32 ;
struct bfa_flash {int op_busy; int type; int residue; int addr_off; void* ubuf; scalar_t__ offset; int /*<<< orphan*/  instance; void* cbarg; int /*<<< orphan*/  cbfn; int /*<<< orphan*/  ioc; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;
typedef  int /*<<< orphan*/  bfa_cb_flash ;

/* Variables and functions */
 int BFA_STATUS_DEVBUSY ; 
 int BFA_STATUS_FLASH_BAD_LEN ; 
 int BFA_STATUS_IOC_NON_OP ; 
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_flash_read_send (struct bfa_flash*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_is_operational (int /*<<< orphan*/ ) ; 

enum bfa_status
bfa_nw_flash_read_part(struct bfa_flash *flash, u32 type, u8 instance,
		       void *buf, u32 len, u32 offset,
		       bfa_cb_flash cbfn, void *cbarg)
{
	if (!bfa_nw_ioc_is_operational(flash->ioc))
		return BFA_STATUS_IOC_NON_OP;

	/*
	 * 'len' must be in word (4-byte) boundary
	 */
	if (!len || (len & 0x03))
		return BFA_STATUS_FLASH_BAD_LEN;

	if (flash->op_busy)
		return BFA_STATUS_DEVBUSY;

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->type = type;
	flash->instance = instance;
	flash->residue = len;
	flash->offset = 0;
	flash->addr_off = offset;
	flash->ubuf = buf;

	bfa_flash_read_send(flash);

	return BFA_STATUS_OK;
}