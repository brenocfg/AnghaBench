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

/* Variables and functions */

__attribute__((used)) static inline u16 repaper_interleave_bits(u16 value)
{
	value = (value | (value << 4)) & 0x0f0f;
	value = (value | (value << 2)) & 0x3333;
	value = (value | (value << 1)) & 0x5555;

	return value;
}