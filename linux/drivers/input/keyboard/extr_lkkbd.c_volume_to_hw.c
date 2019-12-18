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

__attribute__((used)) static unsigned char volume_to_hw(int volume_percent)
{
	unsigned char ret = 0;

	if (volume_percent < 0)
		volume_percent = 0;
	if (volume_percent > 100)
		volume_percent = 100;

	if (volume_percent >= 0)
		ret = 7;
	if (volume_percent >= 13)	/* 12.5 */
		ret = 6;
	if (volume_percent >= 25)
		ret = 5;
	if (volume_percent >= 38)	/* 37.5 */
		ret = 4;
	if (volume_percent >= 50)
		ret = 3;
	if (volume_percent >= 63)	/* 62.5 */
		ret = 2;		/* This is the default volume */
	if (volume_percent >= 75)
		ret = 1;
	if (volume_percent >= 88)	/* 87.5 */
		ret = 0;

	ret |= 0x80;

	return ret;
}