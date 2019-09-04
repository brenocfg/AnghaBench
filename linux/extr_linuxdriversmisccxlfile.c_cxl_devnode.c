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
typedef  int /*<<< orphan*/  umode_t ;
struct device {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 scalar_t__ CXL_DEVT_IS_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *cxl_devnode(struct device *dev, umode_t *mode)
{
	if (cpu_has_feature(CPU_FTR_HVMODE) &&
	    CXL_DEVT_IS_CARD(dev->devt)) {
		/*
		 * These minor numbers will eventually be used to program the
		 * PSL and AFUs once we have dynamic reprogramming support
		 */
		return NULL;
	}
	return kasprintf(GFP_KERNEL, "cxl/%s", dev_name(dev));
}