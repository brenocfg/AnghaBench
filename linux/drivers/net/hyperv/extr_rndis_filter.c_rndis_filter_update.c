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
struct rndis_device {int /*<<< orphan*/  mcast_work; } ;
struct netvsc_device {struct rndis_device* extension; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void rndis_filter_update(struct netvsc_device *nvdev)
{
	struct rndis_device *rdev = nvdev->extension;

	schedule_work(&rdev->mcast_work);
}