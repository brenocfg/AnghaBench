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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static inline u64 swab64(u64 x)
{
	return  (u64)((x & (u64)0x00000000000000ffULL) << 56) |
		(u64)((x & (u64)0x000000000000ff00ULL) << 40) |
		(u64)((x & (u64)0x0000000000ff0000ULL) << 24) |
		(u64)((x & (u64)0x00000000ff000000ULL) <<  8) |
		(u64)((x & (u64)0x000000ff00000000ULL) >>  8) |
		(u64)((x & (u64)0x0000ff0000000000ULL) >> 24) |
		(u64)((x & (u64)0x00ff000000000000ULL) >> 40) |
		(u64)((x & (u64)0xff00000000000000ULL) >> 56);
}