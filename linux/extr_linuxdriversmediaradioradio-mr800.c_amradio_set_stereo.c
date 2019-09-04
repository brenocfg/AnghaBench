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
struct amradio_device {int stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMRADIO_SET_MONO ; 
 int amradio_send_cmd (struct amradio_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amradio_set_stereo(struct amradio_device *radio, bool stereo)
{
	int ret = amradio_send_cmd(radio,
			AMRADIO_SET_MONO, !stereo, NULL, 0, false);

	if (!ret)
		radio->stereo = stereo;
	return ret;
}