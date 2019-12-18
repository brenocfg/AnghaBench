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
struct ipmmu_vmsa_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipmmu_check_device ; 
 scalar_t__ driver_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ipmmu_vmsa_device**,int /*<<< orphan*/ ) ; 
 TYPE_1__ ipmmu_driver ; 

__attribute__((used)) static struct ipmmu_vmsa_device *ipmmu_find_root(void)
{
	struct ipmmu_vmsa_device *root = NULL;

	return driver_for_each_device(&ipmmu_driver.driver, NULL, &root,
				      __ipmmu_check_device) == 0 ? root : NULL;
}