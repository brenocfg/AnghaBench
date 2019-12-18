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
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static long goldfish_audio_ioctl(struct file *fp, unsigned int cmd,
				 unsigned long arg)
{
	/* temporary workaround, until we switch to the ALSA API */
	if (cmd == 315)
		return -1;

	return 0;
}