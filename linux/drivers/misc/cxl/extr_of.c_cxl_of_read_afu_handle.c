#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct cxl_afu {TYPE_1__* guest; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_handle (struct device_node*,int /*<<< orphan*/ *) ; 

int cxl_of_read_afu_handle(struct cxl_afu *afu, struct device_node *afu_np)
{
	if (read_handle(afu_np, &afu->guest->handle))
		return -EINVAL;
	pr_devel("AFU handle: 0x%.16llx\n", afu->guest->handle);

	return 0;
}