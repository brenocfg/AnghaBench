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
struct recurse_struct {int /*<<< orphan*/  obj; scalar_t__ (* fn ) (struct device*,int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int device_for_each_child (struct device*,struct recurse_struct*,int (*) (struct device*,void*)) ; 
 scalar_t__ stub1 (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int descend_children(struct device * dev, void * data)
{
	struct recurse_struct * recurse_data = (struct recurse_struct *)data;

	if (recurse_data->fn(dev, recurse_data->obj))
		return 1;
	else
		return device_for_each_child(dev, recurse_data, descend_children);
}