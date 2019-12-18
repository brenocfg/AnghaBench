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
struct cosm_device {int index; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cosm_index_ida ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 

void cosm_unregister_device(struct cosm_device *dev)
{
	int index = dev->index; /* save for after device release */

	device_unregister(&dev->dev);
	ida_simple_remove(&cosm_index_ida, index);
}