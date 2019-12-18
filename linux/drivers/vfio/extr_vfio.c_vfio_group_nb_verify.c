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
struct vfio_group {int /*<<< orphan*/  container_users; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int vfio_dev_viable (struct device*,struct vfio_group*) ; 

__attribute__((used)) static int vfio_group_nb_verify(struct vfio_group *group, struct device *dev)
{
	/* We don't care what happens when the group isn't in use */
	if (!atomic_read(&group->container_users))
		return 0;

	return vfio_dev_viable(dev, group);
}