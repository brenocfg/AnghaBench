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
struct device {struct device* parent; } ;

/* Variables and functions */
 scalar_t__ dev_is_fsl_mc (struct device*) ; 

__attribute__((used)) static void fsl_mc_get_root_dprc(struct device *dev,
				 struct device **root_dprc_dev)
{
	if (!dev) {
		*root_dprc_dev = NULL;
	} else if (!dev_is_fsl_mc(dev)) {
		*root_dprc_dev = NULL;
	} else {
		*root_dprc_dev = dev;
		while (dev_is_fsl_mc((*root_dprc_dev)->parent))
			*root_dprc_dev = (*root_dprc_dev)->parent;
	}
}