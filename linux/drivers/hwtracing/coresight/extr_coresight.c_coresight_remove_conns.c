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
struct coresight_device {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ nr_inport; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct coresight_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coresight_bustype ; 
 int /*<<< orphan*/  coresight_remove_match ; 

__attribute__((used)) static void coresight_remove_conns(struct coresight_device *csdev)
{
	/*
	 * Another device will point to this device only if there is
	 * an output port connected to this one. i.e, if the device
	 * doesn't have at least one input port, there is no point
	 * in searching all the devices.
	 */
	if (csdev->pdata->nr_inport)
		bus_for_each_dev(&coresight_bustype, NULL,
				 csdev, coresight_remove_match);
}