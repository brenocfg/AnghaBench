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
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 scalar_t__ WARN_ON (int) ; 
 char const** drm_mode_status_names ; 

const char *drm_get_mode_status_name(enum drm_mode_status status)
{
	int index = status + 3;

	if (WARN_ON(index < 0 || index >= ARRAY_SIZE(drm_mode_status_names)))
		return "";

	return drm_mode_status_names[index];
}