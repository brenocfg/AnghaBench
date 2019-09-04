#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct msc {scalar_t__ mode; int base_addr; int nr_pages; int burst_len; int enabled; TYPE_2__* thdev; scalar_t__ reg_base; scalar_t__ wrap; int /*<<< orphan*/  buf_mutex; } ;
struct TYPE_3__ {int multiblock; } ;
struct TYPE_4__ {TYPE_1__ output; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int MSC_EN ; 
 int MSC_LEN ; 
 int MSC_MODE ; 
 scalar_t__ MSC_MODE_MULTI ; 
 scalar_t__ MSC_MODE_SINGLE ; 
 int MSC_RD_HDR_OVRD ; 
 int MSC_WRAPEN ; 
 int PAGE_SHIFT ; 
 scalar_t__ REG_MSU_MSC0BAR ; 
 scalar_t__ REG_MSU_MSC0CTL ; 
 scalar_t__ REG_MSU_MSC0SIZE ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  intel_th_trace_enable (TYPE_2__*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msc_buffer_clear_hw_header (struct msc*) ; 

__attribute__((used)) static int msc_configure(struct msc *msc)
{
	u32 reg;

	lockdep_assert_held(&msc->buf_mutex);

	if (msc->mode > MSC_MODE_MULTI)
		return -ENOTSUPP;

	if (msc->mode == MSC_MODE_MULTI)
		msc_buffer_clear_hw_header(msc);

	reg = msc->base_addr >> PAGE_SHIFT;
	iowrite32(reg, msc->reg_base + REG_MSU_MSC0BAR);

	if (msc->mode == MSC_MODE_SINGLE) {
		reg = msc->nr_pages;
		iowrite32(reg, msc->reg_base + REG_MSU_MSC0SIZE);
	}

	reg = ioread32(msc->reg_base + REG_MSU_MSC0CTL);
	reg &= ~(MSC_MODE | MSC_WRAPEN | MSC_EN | MSC_RD_HDR_OVRD);

	reg |= MSC_EN;
	reg |= msc->mode << __ffs(MSC_MODE);
	reg |= msc->burst_len << __ffs(MSC_LEN);

	if (msc->wrap)
		reg |= MSC_WRAPEN;

	iowrite32(reg, msc->reg_base + REG_MSU_MSC0CTL);

	msc->thdev->output.multiblock = msc->mode == MSC_MODE_MULTI;
	intel_th_trace_enable(msc->thdev);
	msc->enabled = 1;


	return 0;
}