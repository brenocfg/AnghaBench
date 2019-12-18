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
struct xsdfec_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  error_data_lock; scalar_t__ cecc_count; scalar_t__ uecc_count; scalar_t__ isr_err_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsdfec_clear_stats(struct xsdfec_dev *xsdfec)
{
	spin_lock_irqsave(&xsdfec->error_data_lock, xsdfec->flags);
	xsdfec->isr_err_count = 0;
	xsdfec->uecc_count = 0;
	xsdfec->cecc_count = 0;
	spin_unlock_irqrestore(&xsdfec->error_data_lock, xsdfec->flags);

	return 0;
}