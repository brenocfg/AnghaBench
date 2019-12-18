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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int dm_block_t ;

/* Variables and functions */

__attribute__((used)) static void unpack_block_time(uint64_t v, dm_block_t *b, uint32_t *t)
{
	*b = v >> 24;
	*t = v & ((1 << 24) - 1);
}