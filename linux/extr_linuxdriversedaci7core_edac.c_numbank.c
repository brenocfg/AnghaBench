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
#define  EINVAL 128 

__attribute__((used)) static inline int numbank(u32 bank)
{
	static const int banks[] = { 4, 8, 16, -EINVAL };

	return banks[bank & 0x3];
}