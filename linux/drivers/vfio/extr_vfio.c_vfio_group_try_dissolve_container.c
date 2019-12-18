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
 int /*<<< orphan*/  __vfio_group_unset_container (struct vfio_group*) ; 
 scalar_t__ atomic_dec_if_positive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_group_try_dissolve_container(struct vfio_group *group)
{
	if (0 == atomic_dec_if_positive(&group->container_users))
		__vfio_group_unset_container(group);
}