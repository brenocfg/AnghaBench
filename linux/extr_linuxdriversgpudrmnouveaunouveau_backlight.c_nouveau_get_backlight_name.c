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
struct backlight_connector {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_NAME_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bl_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool
nouveau_get_backlight_name(char backlight_name[BL_NAME_SIZE], struct backlight_connector
		*connector)
{
	const int nb = ida_simple_get(&bl_ida, 0, 0, GFP_KERNEL);
	if (nb < 0 || nb >= 100)
		return false;
	if (nb > 0)
		snprintf(backlight_name, BL_NAME_SIZE, "nv_backlight%d", nb);
	else
		snprintf(backlight_name, BL_NAME_SIZE, "nv_backlight");
	connector->id = nb;
	return true;
}