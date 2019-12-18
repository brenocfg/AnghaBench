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

__attribute__((used)) static int gainify(int in)
{
	/*
	 * TODO: check if there are any issues with corner cases
	 * 0x000 (0):0x07F (127): regL
	 * 0x080 (128) - 0x0FF (255): regM, regL
	 * 0x100 (256) - max: regH, regM, regL
	 */
	if (in <= 0x7F)
		return 0x1000 | in;
	else if (in <= 0xFF)
		return 0x1080 | in / 2;
	else
		return 0x1180 | in / 4;
}