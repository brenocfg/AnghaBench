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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_usage_sem_reg; int /*<<< orphan*/  ioc_usage_reg; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 scalar_t__ BFA_IOC_FWIMG_MINSZ ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ bfa_cb_image_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_asic_gen (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_sem_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_sem_release (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_ct_firmware_unlock(struct bfa_ioc *ioc)
{
	u32 usecnt;

	/**
	 * If bios boot (flash based) -- do not decrement usage count
	 */
	if (bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc)) <
						BFA_IOC_FWIMG_MINSZ)
		return;

	/**
	 * decrement usage count
	 */
	bfa_nw_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = readl(ioc->ioc_regs.ioc_usage_reg);
	BUG_ON(!(usecnt > 0));

	usecnt--;
	writel(usecnt, ioc->ioc_regs.ioc_usage_reg);

	bfa_nw_ioc_sem_release(ioc->ioc_regs.ioc_usage_sem_reg);
}