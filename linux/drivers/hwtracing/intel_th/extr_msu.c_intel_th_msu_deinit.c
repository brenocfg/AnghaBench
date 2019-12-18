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
typedef  int /*<<< orphan*/  u32 ;
struct msc {scalar_t__ msu_base; scalar_t__ index; int /*<<< orphan*/  do_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M0BLIE ; 
 int /*<<< orphan*/  M1BLIE ; 
 scalar_t__ REG_MSU_MINTCTL ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_th_msu_deinit(struct msc *msc)
{
	u32 mintctl;

	if (!msc->do_irq)
		return;

	mintctl = ioread32(msc->msu_base + REG_MSU_MINTCTL);
	mintctl &= msc->index ? ~M1BLIE : ~M0BLIE;
	iowrite32(mintctl, msc->msu_base + REG_MSU_MINTCTL);
}