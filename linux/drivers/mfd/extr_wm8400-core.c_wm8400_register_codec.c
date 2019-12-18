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
struct wm8400 {int /*<<< orphan*/  dev; } ;
struct mfd_cell {char* name; int pdata_size; struct wm8400* platform_data; } ;

/* Variables and functions */
 int devm_mfd_add_devices (int /*<<< orphan*/ ,int,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm8400_register_codec(struct wm8400 *wm8400)
{
	const struct mfd_cell cell = {
		.name = "wm8400-codec",
		.platform_data = wm8400,
		.pdata_size = sizeof(*wm8400),
	};

	return devm_mfd_add_devices(wm8400->dev, -1, &cell, 1, NULL, 0, NULL);
}