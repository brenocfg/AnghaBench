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
struct picolcd_data {int /*<<< orphan*/  lcd_contrast; int /*<<< orphan*/  lcd; } ;

/* Variables and functions */
 int picolcd_set_contrast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int picolcd_resume_lcd(struct picolcd_data *data)
{
	if (!data->lcd)
		return 0;
	return picolcd_set_contrast(data->lcd, data->lcd_contrast);
}