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
struct wl1273_core {unsigned int volume; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int WL1273_MAX_VOLUME ; 
 int /*<<< orphan*/  WL1273_VOLUME_SET ; 
 int wl1273_fm_write_cmd (struct wl1273_core*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wl1273_fm_set_volume(struct wl1273_core *core, unsigned int volume)
{
	int r;

	if (volume > WL1273_MAX_VOLUME)
		return -EINVAL;

	if (core->volume == volume)
		return 0;

	r = wl1273_fm_write_cmd(core, WL1273_VOLUME_SET, volume);
	if (r)
		return r;

	core->volume = volume;
	return 0;
}