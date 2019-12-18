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
struct vfio_group {int /*<<< orphan*/  container; } ;

/* Variables and functions */
 long vfio_ioctl_check_extension (int /*<<< orphan*/ ,unsigned long) ; 

long vfio_external_check_extension(struct vfio_group *group, unsigned long arg)
{
	return vfio_ioctl_check_extension(group->container, arg);
}