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
struct arm_ccn {scalar_t__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CCN_MN_ERRINT_STATUS ; 
 int /*<<< orphan*/  CCN_MN_ERRINT_STATUS__ALL_ERRORS__DISABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t arm_ccn_error_handler(struct arm_ccn *ccn,
		const u32 *err_sig_val)
{
	/* This should be really handled by firmware... */
	dev_err(ccn->dev, "Error reported in %08x%08x%08x%08x%08x%08x.\n",
			err_sig_val[5], err_sig_val[4], err_sig_val[3],
			err_sig_val[2], err_sig_val[1], err_sig_val[0]);
	dev_err(ccn->dev, "Disabling interrupt generation for all errors.\n");
	writel(CCN_MN_ERRINT_STATUS__ALL_ERRORS__DISABLE,
			ccn->base + CCN_MN_ERRINT_STATUS);

	return IRQ_HANDLED;
}