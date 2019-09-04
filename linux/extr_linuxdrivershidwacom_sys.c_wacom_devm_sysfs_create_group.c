#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wacom {TYPE_2__* hdev; } ;
struct attribute_group {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int __wacom_devm_sysfs_create_group (struct wacom*,int /*<<< orphan*/ *,struct attribute_group*) ; 

__attribute__((used)) static int wacom_devm_sysfs_create_group(struct wacom *wacom,
					 struct attribute_group *group)
{
	return __wacom_devm_sysfs_create_group(wacom, &wacom->hdev->dev.kobj,
					       group);
}