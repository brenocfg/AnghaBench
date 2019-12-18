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
struct soc_camera_format_xlate {TYPE_1__* host_fmt; } ;
struct soc_camera_device {unsigned int num_user_formats; struct soc_camera_format_xlate const* user_formats; } ;
struct TYPE_2__ {unsigned int fourcc; } ;

/* Variables and functions */

const struct soc_camera_format_xlate *soc_camera_xlate_by_fourcc(
	struct soc_camera_device *icd, unsigned int fourcc)
{
	unsigned int i;

	for (i = 0; i < icd->num_user_formats; i++)
		if (icd->user_formats[i].host_fmt->fourcc == fourcc)
			return icd->user_formats + i;
	return NULL;
}