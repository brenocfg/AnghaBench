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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwlock; int /*<<< orphan*/  socinfo; } ;

/* Variables and functions */
 TYPE_1__* __smem ; 
 int /*<<< orphan*/  hwspin_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_smem_remove(struct platform_device *pdev)
{
	platform_device_unregister(__smem->socinfo);

	hwspin_lock_free(__smem->hwlock);
	__smem = NULL;

	return 0;
}