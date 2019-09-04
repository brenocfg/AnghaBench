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
struct unicam_fmt {scalar_t__ code; } ;
struct unicam_device {unsigned int num_active_fmt; struct unicam_fmt* active_fmts; } ;

/* Variables and functions */

__attribute__((used)) static const struct unicam_fmt *find_format_by_code(struct unicam_device *dev,
						    u32 code)
{
	const struct unicam_fmt *fmt;
	unsigned int k;

	for (k = 0; k < dev->num_active_fmt; k++) {
		fmt = &dev->active_fmts[k];
		if (fmt->code == code)
			return fmt;
	}

	return NULL;
}