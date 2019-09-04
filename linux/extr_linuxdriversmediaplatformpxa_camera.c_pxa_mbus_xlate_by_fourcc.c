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
typedef  struct pxa_camera_format_xlate {TYPE_1__* host_fmt; scalar_t__ code; } const pxa_camera_format_xlate ;
struct TYPE_2__ {unsigned int fourcc; } ;

/* Variables and functions */

__attribute__((used)) static const struct pxa_camera_format_xlate
*pxa_mbus_xlate_by_fourcc(struct pxa_camera_format_xlate *user_formats,
			  unsigned int fourcc)
{
	unsigned int i;

	for (i = 0; user_formats[i].code; i++)
		if (user_formats[i].host_fmt->fourcc == fourcc)
			return user_formats + i;
	return NULL;
}