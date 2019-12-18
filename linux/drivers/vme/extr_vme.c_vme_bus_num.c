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
struct vme_dev {struct vme_bridge* bridge; } ;
struct vme_bridge {int num; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int vme_bus_num(struct vme_dev *vdev)
{
	struct vme_bridge *bridge;

	bridge = vdev->bridge;
	if (!bridge) {
		pr_err("Can't find VME bus\n");
		return -EINVAL;
	}

	return bridge->num;
}