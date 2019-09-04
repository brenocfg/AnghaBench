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
typedef  int u8 ;
typedef  int u32 ;
struct edid {int revision; } ;

/* Variables and functions */

__attribute__((used)) static u32
range_pixel_clock(struct edid *edid, u8 *t)
{
	/* unspecified */
	if (t[9] == 0 || t[9] == 255)
		return 0;

	/* 1.4 with CVT support gives us real precision, yay */
	if (edid->revision >= 4 && t[10] == 0x04)
		return (t[9] * 10000) - ((t[12] >> 2) * 250);

	/* 1.3 is pathetic, so fuzz up a bit */
	return t[9] * 10000 + 5001;
}