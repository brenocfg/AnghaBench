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
struct tcmu_dev {int /*<<< orphan*/  kref; } ;
struct se_device {int dummy; } ;

/* Variables and functions */
 struct tcmu_dev* TCMU_DEV (struct se_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcmu_dev_kref_release ; 

__attribute__((used)) static void tcmu_free_device(struct se_device *dev)
{
	struct tcmu_dev *udev = TCMU_DEV(dev);

	/* release ref from init */
	kref_put(&udev->kref, tcmu_dev_kref_release);
}