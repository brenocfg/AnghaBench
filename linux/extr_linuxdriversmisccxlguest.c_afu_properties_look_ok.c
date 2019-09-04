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
struct cxl_afu {scalar_t__ pp_irqs; int max_procs_virtualised; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int afu_properties_look_ok(struct cxl_afu *afu)
{
	if (afu->pp_irqs < 0) {
		dev_err(&afu->dev, "Unexpected per-process minimum interrupt value\n");
		return -EINVAL;
	}

	if (afu->max_procs_virtualised < 1) {
		dev_err(&afu->dev, "Unexpected max number of processes virtualised value\n");
		return -EINVAL;
	}

	return 0;
}