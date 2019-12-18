#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct msc {int mode; int base_addr; int nr_pages; int burst_len; int enabled; int /*<<< orphan*/  mbuf_priv; TYPE_2__* mbuf; TYPE_3__* thdev; scalar_t__ reg_base; scalar_t__ wrap; void* orig_sz; void* orig_addr; int /*<<< orphan*/  cur_win; int /*<<< orphan*/  buf_mutex; } ;
struct TYPE_4__ {int multiblock; } ;
struct TYPE_6__ {TYPE_1__ output; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* activate ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTSUPP ; 
 int MSC_EN ; 
 int MSC_LEN ; 
 int MSC_MODE ; 
 int MSC_MODE_MULTI ; 
 int MSC_MODE_SINGLE ; 
 int MSC_RD_HDR_OVRD ; 
 int MSC_WRAPEN ; 
 int PAGE_SHIFT ; 
 scalar_t__ REG_MSU_MSC0BAR ; 
 scalar_t__ REG_MSU_MSC0CTL ; 
 scalar_t__ REG_MSU_MSC0SIZE ; 
 int /*<<< orphan*/  WIN_INUSE ; 
 int /*<<< orphan*/  WIN_READY ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  intel_th_msu_init (struct msc*) ; 
 int /*<<< orphan*/  intel_th_trace_enable (TYPE_3__*) ; 
 void* ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msc_buffer_clear_hw_header (struct msc*) ; 
 scalar_t__ msc_win_set_lockout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msc_configure(struct msc *msc)
{
	u32 reg;

	lockdep_assert_held(&msc->buf_mutex);

	if (msc->mode > MSC_MODE_MULTI)
		return -ENOTSUPP;

	if (msc->mode == MSC_MODE_MULTI) {
		if (msc_win_set_lockout(msc->cur_win, WIN_READY, WIN_INUSE))
			return -EBUSY;

		msc_buffer_clear_hw_header(msc);
	}

	msc->orig_addr = ioread32(msc->reg_base + REG_MSU_MSC0BAR);
	msc->orig_sz   = ioread32(msc->reg_base + REG_MSU_MSC0SIZE);

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

	intel_th_msu_init(msc);

	msc->thdev->output.multiblock = msc->mode == MSC_MODE_MULTI;
	intel_th_trace_enable(msc->thdev);
	msc->enabled = 1;

	if (msc->mbuf && msc->mbuf->activate)
		msc->mbuf->activate(msc->mbuf_priv);

	return 0;
}