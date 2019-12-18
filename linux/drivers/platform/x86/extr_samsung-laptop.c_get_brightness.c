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
struct samsung_laptop {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct samsung_laptop* bl_get_data (struct backlight_device*) ; 
 int read_brightness (struct samsung_laptop*) ; 

__attribute__((used)) static int get_brightness(struct backlight_device *bd)
{
	struct samsung_laptop *samsung = bl_get_data(bd);

	return read_brightness(samsung);
}