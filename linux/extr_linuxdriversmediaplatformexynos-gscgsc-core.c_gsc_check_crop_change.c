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

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void gsc_check_crop_change(u32 tmp_w, u32 tmp_h, u32 *w, u32 *h)
{
	if (tmp_w != *w || tmp_h != *h) {
		pr_info("Cropped size has been modified from %dx%d to %dx%d",
							*w, *h, tmp_w, tmp_h);
		*w = tmp_w;
		*h = tmp_h;
	}
}