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
struct rproc {int dummy; } ;
struct device {struct rproc* driver_data; int /*<<< orphan*/ * type; struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  rproc_type ; 

struct rproc *rproc_get_by_child(struct device *dev)
{
	for (dev = dev->parent; dev; dev = dev->parent) {
		if (dev->type == &rproc_type)
			return dev->driver_data;
	}

	return NULL;
}