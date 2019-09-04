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
struct wiimote_data {int /*<<< orphan*/ * mp; } ;
struct wiimod_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wiimod_mp_remove(const struct wiimod_ops *ops,
			     struct wiimote_data *wdata)
{
	if (!wdata->mp)
		return;

	input_unregister_device(wdata->mp);
	wdata->mp = NULL;
}