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
typedef  scalar_t__ u32 ;
struct shmob_drm_format_info {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct shmob_drm_format_info const*) ; 
 struct shmob_drm_format_info const* shmob_drm_format_infos ; 

const struct shmob_drm_format_info *shmob_drm_format_info(u32 fourcc)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(shmob_drm_format_infos); ++i) {
		if (shmob_drm_format_infos[i].fourcc == fourcc)
			return &shmob_drm_format_infos[i];
	}

	return NULL;
}