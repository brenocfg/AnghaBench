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
 int device_for_each_child (struct device*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_nd_region (struct device*) ; 
 int /*<<< orphan*/  is_uuid_busy ; 

__attribute__((used)) static int is_namespace_uuid_busy(struct device *dev, void *data)
{
	if (is_nd_region(dev))
		return device_for_each_child(dev, data, is_uuid_busy);
	return 0;
}