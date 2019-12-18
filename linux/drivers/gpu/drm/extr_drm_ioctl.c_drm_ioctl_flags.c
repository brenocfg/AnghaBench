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
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 unsigned int DRM_COMMAND_BASE ; 
 unsigned int DRM_COMMAND_END ; 
 unsigned int DRM_CORE_IOCTL_COUNT ; 
 unsigned int array_index_nospec (unsigned int,unsigned int) ; 
 TYPE_1__* drm_ioctls ; 

bool drm_ioctl_flags(unsigned int nr, unsigned int *flags)
{
	if (nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END)
		return false;

	if (nr >= DRM_CORE_IOCTL_COUNT)
		return false;
	nr = array_index_nospec(nr, DRM_CORE_IOCTL_COUNT);

	*flags = drm_ioctls[nr].flags;
	return true;
}