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
struct fsl_mc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mc_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dprc_set_irq_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dprc_set_irq_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int enable_dprc_irq(struct fsl_mc_device *mc_dev)
{
	int error;

	/*
	 * Enable all interrupt causes for the interrupt:
	 */
	error = dprc_set_irq_mask(mc_dev->mc_io, 0, mc_dev->mc_handle, 0,
				  ~0x0u);
	if (error < 0) {
		dev_err(&mc_dev->dev,
			"Enabling DPRC IRQ failed: dprc_set_irq_mask() failed: %d\n",
			error);

		return error;
	}

	/*
	 * Enable generation of the interrupt:
	 */
	error = dprc_set_irq_enable(mc_dev->mc_io, 0, mc_dev->mc_handle, 0, 1);
	if (error < 0) {
		dev_err(&mc_dev->dev,
			"Enabling DPRC IRQ failed: dprc_set_irq_enable() failed: %d\n",
			error);

		return error;
	}

	return 0;
}