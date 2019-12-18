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
struct bfi_flash_erase_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  instance; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_flash_s {TYPE_1__ mb; int /*<<< orphan*/  ioc; int /*<<< orphan*/  instance; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_FLASH_H2I_ERASE_REQ ; 
 int /*<<< orphan*/  BFI_MC_FLASH ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_flash_erase_send(void *cbarg)
{
	struct bfa_flash_s *flash = cbarg;
	struct bfi_flash_erase_req_s *msg =
			(struct bfi_flash_erase_req_s *) flash->mb.msg;

	msg->type = be32_to_cpu(flash->type);
	msg->instance = flash->instance;
	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_ERASE_REQ,
			bfa_ioc_portid(flash->ioc));
	bfa_ioc_mbox_queue(flash->ioc, &flash->mb);
}