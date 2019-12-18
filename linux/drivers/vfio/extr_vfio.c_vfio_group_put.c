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
struct vfio_group {int /*<<< orphan*/  kref; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ vfio ; 
 int /*<<< orphan*/  vfio_group_release ; 

__attribute__((used)) static void vfio_group_put(struct vfio_group *group)
{
	kref_put_mutex(&group->kref, vfio_group_release, &vfio.group_lock);
}