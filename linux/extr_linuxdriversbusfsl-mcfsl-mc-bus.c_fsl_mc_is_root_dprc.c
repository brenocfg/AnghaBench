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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_mc_get_root_dprc (struct device*,struct device**) ; 

bool fsl_mc_is_root_dprc(struct device *dev)
{
	struct device *root_dprc_dev;

	fsl_mc_get_root_dprc(dev, &root_dprc_dev);
	if (!root_dprc_dev)
		return false;
	return dev == root_dprc_dev;
}