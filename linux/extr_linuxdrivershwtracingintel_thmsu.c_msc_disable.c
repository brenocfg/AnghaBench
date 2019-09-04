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
typedef  int u32 ;
struct msc {scalar_t__ mode; int single_wrap; int single_sz; int nr_pages; scalar_t__ reg_base; scalar_t__ enabled; int /*<<< orphan*/  thdev; int /*<<< orphan*/  buf_mutex; } ;

/* Variables and functions */
 int MSCSTS_PLE ; 
 int MSCSTS_WRAPSTAT ; 
 int MSC_EN ; 
 scalar_t__ MSC_MODE_SINGLE ; 
 unsigned long MSC_PLE_WAITLOOP_DEPTH ; 
 int PAGE_SHIFT ; 
 scalar_t__ REG_MSU_MSC0BAR ; 
 scalar_t__ REG_MSU_MSC0CTL ; 
 scalar_t__ REG_MSU_MSC0MWP ; 
 scalar_t__ REG_MSU_MSC0NWSA ; 
 scalar_t__ REG_MSU_MSC0SIZE ; 
 scalar_t__ REG_MSU_MSC0STS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  intel_th_trace_disable (int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msc_dev (struct msc*) ; 

__attribute__((used)) static void msc_disable(struct msc *msc)
{
	unsigned long count;
	u32 reg;

	lockdep_assert_held(&msc->buf_mutex);

	intel_th_trace_disable(msc->thdev);

	for (reg = 0, count = MSC_PLE_WAITLOOP_DEPTH;
	     count && !(reg & MSCSTS_PLE); count--) {
		reg = ioread32(msc->reg_base + REG_MSU_MSC0STS);
		cpu_relax();
	}

	if (!count)
		dev_dbg(msc_dev(msc), "timeout waiting for MSC0 PLE\n");

	if (msc->mode == MSC_MODE_SINGLE) {
		msc->single_wrap = !!(reg & MSCSTS_WRAPSTAT);

		reg = ioread32(msc->reg_base + REG_MSU_MSC0MWP);
		msc->single_sz = reg & ((msc->nr_pages << PAGE_SHIFT) - 1);
		dev_dbg(msc_dev(msc), "MSCnMWP: %08x/%08lx, wrap: %d\n",
			reg, msc->single_sz, msc->single_wrap);
	}

	reg = ioread32(msc->reg_base + REG_MSU_MSC0CTL);
	reg &= ~MSC_EN;
	iowrite32(reg, msc->reg_base + REG_MSU_MSC0CTL);
	msc->enabled = 0;

	iowrite32(0, msc->reg_base + REG_MSU_MSC0BAR);
	iowrite32(0, msc->reg_base + REG_MSU_MSC0SIZE);

	dev_dbg(msc_dev(msc), "MSCnNWSA: %08x\n",
		ioread32(msc->reg_base + REG_MSU_MSC0NWSA));

	reg = ioread32(msc->reg_base + REG_MSU_MSC0STS);
	dev_dbg(msc_dev(msc), "MSCnSTS: %08x\n", reg);
}