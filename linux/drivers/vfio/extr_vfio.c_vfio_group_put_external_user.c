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
struct vfio_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfio_group_put (struct vfio_group*) ; 
 int /*<<< orphan*/  vfio_group_try_dissolve_container (struct vfio_group*) ; 

void vfio_group_put_external_user(struct vfio_group *group)
{
	vfio_group_try_dissolve_container(group);
	vfio_group_put(group);
}