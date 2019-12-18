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
struct bfi_ioc_image_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_usage_sem_reg; int /*<<< orphan*/  ioc_usage_reg; int /*<<< orphan*/  ioc_fwstate; int /*<<< orphan*/  ioc_fail_sync; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;
typedef  enum bfi_ioc_state { ____Placeholder_bfi_ioc_state } bfi_ioc_state ;

/* Variables and functions */
 scalar_t__ BFA_IOC_FWIMG_MINSZ ; 
 int BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ bfa_cb_image_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_asic_gen (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_fwver_cmp (struct bfa_ioc*,struct bfi_ioc_image_hdr*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_fwver_get (struct bfa_ioc*,struct bfi_ioc_image_hdr*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_sem_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_sem_release (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bfa_ioc_ct_firmware_lock(struct bfa_ioc *ioc)
{
	enum bfi_ioc_state ioc_fwstate;
	u32 usecnt;
	struct bfi_ioc_image_hdr fwhdr;

	/**
	 * If bios boot (flash based) -- do not increment usage count
	 */
	if (bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc)) <
						BFA_IOC_FWIMG_MINSZ)
		return true;

	bfa_nw_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = readl(ioc->ioc_regs.ioc_usage_reg);

	/**
	 * If usage count is 0, always return TRUE.
	 */
	if (usecnt == 0) {
		writel(1, ioc->ioc_regs.ioc_usage_reg);
		bfa_nw_ioc_sem_release(ioc->ioc_regs.ioc_usage_sem_reg);
		writel(0, ioc->ioc_regs.ioc_fail_sync);
		return true;
	}

	ioc_fwstate = readl(ioc->ioc_regs.ioc_fwstate);

	/**
	 * Use count cannot be non-zero and chip in uninitialized state.
	 */
	BUG_ON(!(ioc_fwstate != BFI_IOC_UNINIT));

	/**
	 * Check if another driver with a different firmware is active
	 */
	bfa_nw_ioc_fwver_get(ioc, &fwhdr);
	if (!bfa_nw_ioc_fwver_cmp(ioc, &fwhdr)) {
		bfa_nw_ioc_sem_release(ioc->ioc_regs.ioc_usage_sem_reg);
		return false;
	}

	/**
	 * Same firmware version. Increment the reference count.
	 */
	usecnt++;
	writel(usecnt, ioc->ioc_regs.ioc_usage_reg);
	bfa_nw_ioc_sem_release(ioc->ioc_regs.ioc_usage_sem_reg);
	return true;
}