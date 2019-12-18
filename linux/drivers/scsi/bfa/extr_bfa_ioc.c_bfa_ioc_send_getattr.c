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
struct bfi_ioc_getattr_req_s {int /*<<< orphan*/  attr_addr; int /*<<< orphan*/  mh; } ;
struct TYPE_2__ {int /*<<< orphan*/  pa; } ;
struct bfa_ioc_s {TYPE_1__ attr_dma; } ;
typedef  int /*<<< orphan*/  attr_req ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_H2I_GETATTR_REQ ; 
 int /*<<< orphan*/  BFI_MC_IOC ; 
 int /*<<< orphan*/  bfa_dma_be_addr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_send (struct bfa_ioc_s*,struct bfi_ioc_getattr_req_s*,int) ; 
 int /*<<< orphan*/  bfa_ioc_portid (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_send_getattr(struct bfa_ioc_s *ioc)
{
	struct bfi_ioc_getattr_req_s	attr_req;

	bfi_h2i_set(attr_req.mh, BFI_MC_IOC, BFI_IOC_H2I_GETATTR_REQ,
		    bfa_ioc_portid(ioc));
	bfa_dma_be_addr_set(attr_req.attr_addr, ioc->attr_dma.pa);
	bfa_ioc_mbox_send(ioc, &attr_req, sizeof(attr_req));
}