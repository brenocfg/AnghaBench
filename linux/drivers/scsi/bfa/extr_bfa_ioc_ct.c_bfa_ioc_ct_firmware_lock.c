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
struct bfi_ioc_image_hdr_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_usage_sem_reg; int /*<<< orphan*/  ioc_usage_reg; int /*<<< orphan*/  ioc_fwstate; int /*<<< orphan*/  ioc_fail_sync; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;
typedef  enum bfi_ioc_state { ____Placeholder_bfi_ioc_state } bfi_ioc_state ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_cmp (struct bfa_ioc_s*,struct bfi_ioc_image_hdr_s*) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_get (struct bfa_ioc_s*,struct bfi_ioc_image_hdr_s*) ; 
 int /*<<< orphan*/  bfa_ioc_sem_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_ct_firmware_lock(struct bfa_ioc_s *ioc)
{
	enum bfi_ioc_state ioc_fwstate;
	u32 usecnt;
	struct bfi_ioc_image_hdr_s fwhdr;

	bfa_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = readl(ioc->ioc_regs.ioc_usage_reg);

	/*
	 * If usage count is 0, always return TRUE.
	 */
	if (usecnt == 0) {
		writel(1, ioc->ioc_regs.ioc_usage_reg);
		readl(ioc->ioc_regs.ioc_usage_sem_reg);
		writel(1, ioc->ioc_regs.ioc_usage_sem_reg);
		writel(0, ioc->ioc_regs.ioc_fail_sync);
		bfa_trc(ioc, usecnt);
		return BFA_TRUE;
	}

	ioc_fwstate = readl(ioc->ioc_regs.ioc_fwstate);
	bfa_trc(ioc, ioc_fwstate);

	/*
	 * Use count cannot be non-zero and chip in uninitialized state.
	 */
	WARN_ON(ioc_fwstate == BFI_IOC_UNINIT);

	/*
	 * Check if another driver with a different firmware is active
	 */
	bfa_ioc_fwver_get(ioc, &fwhdr);
	if (!bfa_ioc_fwver_cmp(ioc, &fwhdr)) {
		readl(ioc->ioc_regs.ioc_usage_sem_reg);
		writel(1, ioc->ioc_regs.ioc_usage_sem_reg);
		bfa_trc(ioc, usecnt);
		return BFA_FALSE;
	}

	/*
	 * Same firmware version. Increment the reference count.
	 */
	usecnt++;
	writel(usecnt, ioc->ioc_regs.ioc_usage_reg);
	readl(ioc->ioc_regs.ioc_usage_sem_reg);
	writel(1, ioc->ioc_regs.ioc_usage_sem_reg);
	bfa_trc(ioc, usecnt);
	return BFA_TRUE;
}