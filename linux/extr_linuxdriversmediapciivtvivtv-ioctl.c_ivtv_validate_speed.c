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

/* Variables and functions */

__attribute__((used)) static int ivtv_validate_speed(int cur_speed, int new_speed)
{
	int fact = new_speed < 0 ? -1 : 1;
	int s;

	if (cur_speed == 0)
		cur_speed = 1000;
	if (new_speed < 0)
		new_speed = -new_speed;
	if (cur_speed < 0)
		cur_speed = -cur_speed;

	if (cur_speed <= new_speed) {
		if (new_speed > 1500)
			return fact * 2000;
		if (new_speed > 1000)
			return fact * 1500;
	}
	else {
		if (new_speed >= 2000)
			return fact * 2000;
		if (new_speed >= 1500)
			return fact * 1500;
		if (new_speed >= 1000)
			return fact * 1000;
	}
	if (new_speed == 0)
		return 1000;
	if (new_speed == 1 || new_speed == 1000)
		return fact * new_speed;

	s = new_speed;
	new_speed = 1000 / new_speed;
	if (1000 / cur_speed == new_speed)
		new_speed += (cur_speed < s) ? -1 : 1;
	if (new_speed > 60) return 1000 / (fact * 60);
	return 1000 / (fact * new_speed);
}