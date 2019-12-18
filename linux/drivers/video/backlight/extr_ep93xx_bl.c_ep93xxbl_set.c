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
struct ep93xxbl {int brightness; int /*<<< orphan*/  mmio; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int EP93XX_MAX_COUNT ; 
 struct ep93xxbl* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xxbl_set(struct backlight_device *bl, int brightness)
{
	struct ep93xxbl *ep93xxbl = bl_get_data(bl);

	writel((brightness << 8) | EP93XX_MAX_COUNT, ep93xxbl->mmio);

	ep93xxbl->brightness = brightness;

	return 0;
}