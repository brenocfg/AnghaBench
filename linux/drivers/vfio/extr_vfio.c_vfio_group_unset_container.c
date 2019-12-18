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

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  __vfio_group_unset_container (struct vfio_group*) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_group_unset_container(struct vfio_group *group)
{
	int users = atomic_cmpxchg(&group->container_users, 1, 0);

	if (!users)
		return -EINVAL;
	if (users != 1)
		return -EBUSY;

	__vfio_group_unset_container(group);

	return 0;
}