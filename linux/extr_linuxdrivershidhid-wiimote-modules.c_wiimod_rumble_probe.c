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
struct wiimote_data {TYPE_1__* input; int /*<<< orphan*/  rumble_worker; } ;
struct wiimod_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ffbit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ input_ff_create_memless (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiimod_rumble_play ; 
 int /*<<< orphan*/  wiimod_rumble_worker ; 

__attribute__((used)) static int wiimod_rumble_probe(const struct wiimod_ops *ops,
			       struct wiimote_data *wdata)
{
	INIT_WORK(&wdata->rumble_worker, wiimod_rumble_worker);

	set_bit(FF_RUMBLE, wdata->input->ffbit);
	if (input_ff_create_memless(wdata->input, NULL, wiimod_rumble_play))
		return -ENOMEM;

	return 0;
}