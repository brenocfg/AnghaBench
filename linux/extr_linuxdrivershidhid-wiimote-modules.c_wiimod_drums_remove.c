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
struct TYPE_2__ {int /*<<< orphan*/ * input; } ;
struct wiimote_data {TYPE_1__ extension; } ;
struct wiimod_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wiimod_drums_remove(const struct wiimod_ops *ops,
				struct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		return;

	input_unregister_device(wdata->extension.input);
	wdata->extension.input = NULL;
}