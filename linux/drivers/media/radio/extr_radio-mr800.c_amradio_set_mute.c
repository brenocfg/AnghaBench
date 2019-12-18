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
struct amradio_device {int muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMRADIO_SET_MUTE ; 
 int amradio_send_cmd (struct amradio_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amradio_set_mute(struct amradio_device *radio, bool mute)
{
	int ret = amradio_send_cmd(radio,
			AMRADIO_SET_MUTE, mute, NULL, 0, false);

	if (!ret)
		radio->muted = mute;
	return ret;
}