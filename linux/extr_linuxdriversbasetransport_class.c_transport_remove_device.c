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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attribute_container_device_trigger (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_remove_classdev ; 

void transport_remove_device(struct device *dev)
{
	attribute_container_device_trigger(dev, transport_remove_classdev);
}