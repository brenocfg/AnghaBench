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
typedef  unsigned char uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t hash(unsigned offset)
{
	unsigned v = offset;
	unsigned char c;
	v ^= 0x7f7edfd3;
	v = v ^ (v >> 3);
	v = v ^ (v >> 5);
	v = v ^ (v >> 13);
	c = v & 0xFF;
	/* Reverse bits of result. */
	c = (c & 0x0F) << 4 | (c & 0xF0) >> 4;
	c = (c & 0x33) << 2 | (c & 0xCC) >> 2;
	c = (c & 0x55) << 1 | (c & 0xAA) >> 1;
	return c;
}