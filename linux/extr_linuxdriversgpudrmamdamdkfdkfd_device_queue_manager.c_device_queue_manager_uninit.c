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
struct TYPE_2__ {int /*<<< orphan*/  (* uninitialize ) (struct device_queue_manager*) ;} ;
struct device_queue_manager {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct device_queue_manager*) ; 
 int /*<<< orphan*/  stub1 (struct device_queue_manager*) ; 

void device_queue_manager_uninit(struct device_queue_manager *dqm)
{
	dqm->ops.uninitialize(dqm);
	kfree(dqm);
}