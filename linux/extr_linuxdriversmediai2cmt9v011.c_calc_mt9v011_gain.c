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
typedef  int u16 ;
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static u16 calc_mt9v011_gain(s16 lineargain)
{

	u16 digitalgain = 0;
	u16 analogmult = 0;
	u16 analoginit = 0;

	if (lineargain < 0)
		lineargain = 0;

	/* recommended minimum */
	lineargain += 0x0020;

	if (lineargain > 2047)
		lineargain = 2047;

	if (lineargain > 1023) {
		digitalgain = 3;
		analogmult = 3;
		analoginit = lineargain / 16;
	} else if (lineargain > 511) {
		digitalgain = 1;
		analogmult = 3;
		analoginit = lineargain / 8;
	} else if (lineargain > 255) {
		analogmult = 3;
		analoginit = lineargain / 4;
	} else if (lineargain > 127) {
		analogmult = 1;
		analoginit = lineargain / 2;
	} else
		analoginit = lineargain;

	return analoginit + (analogmult << 7) + (digitalgain << 9);

}