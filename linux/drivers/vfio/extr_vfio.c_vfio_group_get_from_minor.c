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
struct vfio_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_lock; int /*<<< orphan*/  group_idr; } ;

/* Variables and functions */
 struct vfio_group* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ vfio ; 
 int /*<<< orphan*/  vfio_group_get (struct vfio_group*) ; 

__attribute__((used)) static struct vfio_group *vfio_group_get_from_minor(int minor)
{
	struct vfio_group *group;

	mutex_lock(&vfio.group_lock);
	group = idr_find(&vfio.group_idr, minor);
	if (!group) {
		mutex_unlock(&vfio.group_lock);
		return NULL;
	}
	vfio_group_get(group);
	mutex_unlock(&vfio.group_lock);

	return group;
}