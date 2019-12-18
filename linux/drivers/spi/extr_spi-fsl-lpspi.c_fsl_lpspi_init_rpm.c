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
struct fsl_lpspi_data {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_LPSPI_RPM_TIMEOUT ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

__attribute__((used)) static int fsl_lpspi_init_rpm(struct fsl_lpspi_data *fsl_lpspi)
{
	struct device *dev = fsl_lpspi->dev;

	pm_runtime_enable(dev);
	pm_runtime_set_autosuspend_delay(dev, FSL_LPSPI_RPM_TIMEOUT);
	pm_runtime_use_autosuspend(dev);

	return 0;
}