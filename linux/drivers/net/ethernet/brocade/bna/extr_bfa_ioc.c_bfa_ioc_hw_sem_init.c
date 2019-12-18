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
typedef  int u32 ;
struct bfi_ioc_image_hdr {int /*<<< orphan*/  exec; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_init_sem_reg; int /*<<< orphan*/  ioc_sem_reg; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 scalar_t__ BFI_FWBOOT_TYPE_NORMAL ; 
 int BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  bfa_ioc_fwver_clear (struct bfa_ioc*) ; 
 int bfa_ioc_get_cur_ioc_fwstate (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_set_alt_ioc_fwstate (struct bfa_ioc*,int) ; 
 int /*<<< orphan*/  bfa_ioc_set_cur_ioc_fwstate (struct bfa_ioc*,int) ; 
 int /*<<< orphan*/  bfa_nw_ioc_fwver_get (struct bfa_ioc*,struct bfi_ioc_image_hdr*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_hw_sem_init(struct bfa_ioc *ioc)
{
	struct bfi_ioc_image_hdr fwhdr;
	u32 fwstate, r32;

	/* Spin on init semaphore to serialize. */
	r32 = readl(ioc->ioc_regs.ioc_init_sem_reg);
	while (r32 & 0x1) {
		udelay(20);
		r32 = readl(ioc->ioc_regs.ioc_init_sem_reg);
	}

	fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);
	if (fwstate == BFI_IOC_UNINIT) {
		writel(1, ioc->ioc_regs.ioc_init_sem_reg);
		return;
	}

	bfa_nw_ioc_fwver_get(ioc, &fwhdr);

	if (swab32(fwhdr.exec) == BFI_FWBOOT_TYPE_NORMAL) {
		writel(1, ioc->ioc_regs.ioc_init_sem_reg);
		return;
	}

	bfa_ioc_fwver_clear(ioc);
	bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_UNINIT);

	/*
	 * Try to lock and then unlock the semaphore.
	 */
	readl(ioc->ioc_regs.ioc_sem_reg);
	writel(1, ioc->ioc_regs.ioc_sem_reg);

	/* Unlock init semaphore */
	writel(1, ioc->ioc_regs.ioc_init_sem_reg);
}