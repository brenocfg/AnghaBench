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
typedef  int __u32 ;

/* Variables and functions */

__attribute__((used)) static inline int pvrdma_idx_valid(__u32 idx, __u32 max_elems)
{
	/* Generates fewer instructions than a less-than. */
	return (idx & ~((max_elems << 1) - 1)) == 0;
}