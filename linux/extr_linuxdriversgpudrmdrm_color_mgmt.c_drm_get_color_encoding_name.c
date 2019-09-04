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
typedef  enum drm_color_encoding { ____Placeholder_drm_color_encoding } drm_color_encoding ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 scalar_t__ WARN_ON (int) ; 
 char const** color_encoding_name ; 

const char *drm_get_color_encoding_name(enum drm_color_encoding encoding)
{
	if (WARN_ON(encoding >= ARRAY_SIZE(color_encoding_name)))
		return "unknown";

	return color_encoding_name[encoding];
}