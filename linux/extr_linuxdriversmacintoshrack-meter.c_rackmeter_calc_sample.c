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
typedef  int u32 ;
struct rackmeter {int* ubuf; } ;

/* Variables and functions */

__attribute__((used)) static u32 rackmeter_calc_sample(struct rackmeter *rm, unsigned int index)
{
	int led;
	u32 sample = 0;

	for (led = 0; led < 16; led++) {
		sample >>= 1;
		sample |= ((rm->ubuf[led] >= 0x80) << 15);
	}
	return (sample << 17) | (sample >> 15);
}