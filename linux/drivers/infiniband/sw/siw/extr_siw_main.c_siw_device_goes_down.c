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
struct siw_device {int /*<<< orphan*/  netdev_down; int /*<<< orphan*/  base_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_device_try_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_netdev_down ; 

__attribute__((used)) static void siw_device_goes_down(struct siw_device *sdev)
{
	if (ib_device_try_get(&sdev->base_dev)) {
		INIT_WORK(&sdev->netdev_down, siw_netdev_down);
		schedule_work(&sdev->netdev_down);
	}
}