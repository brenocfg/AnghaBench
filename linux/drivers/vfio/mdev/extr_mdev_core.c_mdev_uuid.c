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
struct mdev_device {int /*<<< orphan*/  const uuid; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */

const guid_t *mdev_uuid(struct mdev_device *mdev)
{
	return &mdev->uuid;
}