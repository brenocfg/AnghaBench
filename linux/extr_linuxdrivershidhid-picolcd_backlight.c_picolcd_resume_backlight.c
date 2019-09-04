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
struct picolcd_data {int /*<<< orphan*/  backlight; } ;

/* Variables and functions */
 int picolcd_set_brightness (int /*<<< orphan*/ ) ; 

int picolcd_resume_backlight(struct picolcd_data *data)
{
	if (!data->backlight)
		return 0;
	return picolcd_set_brightness(data->backlight);
}