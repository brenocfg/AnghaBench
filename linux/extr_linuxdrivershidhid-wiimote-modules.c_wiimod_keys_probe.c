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
struct wiimote_data {TYPE_1__* input; } ;
struct wiimod_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 unsigned int WIIPROTO_KEY_COUNT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wiimod_keys_map ; 

__attribute__((used)) static int wiimod_keys_probe(const struct wiimod_ops *ops,
			     struct wiimote_data *wdata)
{
	unsigned int i;

	set_bit(EV_KEY, wdata->input->evbit);
	for (i = 0; i < WIIPROTO_KEY_COUNT; ++i)
		set_bit(wiimod_keys_map[i], wdata->input->keybit);

	return 0;
}