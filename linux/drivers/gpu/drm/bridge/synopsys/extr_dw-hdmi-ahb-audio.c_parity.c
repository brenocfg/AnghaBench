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

/* Variables and functions */

__attribute__((used)) static u32 parity(u32 sample)
{
	sample ^= sample >> 16;
	sample ^= sample >> 8;
	sample ^= sample >> 4;
	sample ^= sample >> 2;
	sample ^= sample >> 1;
	return (sample & 1) << 27;
}