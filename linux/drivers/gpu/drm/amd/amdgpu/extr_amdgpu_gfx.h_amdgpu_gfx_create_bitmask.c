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
typedef  unsigned long long u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 amdgpu_gfx_create_bitmask(u32 bit_width)
{
	return (u32)((1ULL << bit_width) - 1);
}