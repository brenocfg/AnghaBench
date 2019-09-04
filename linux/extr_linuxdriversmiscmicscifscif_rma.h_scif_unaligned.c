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
typedef  int off_t ;

/* Variables and functions */
 int L1_CACHE_BYTES ; 

__attribute__((used)) static inline bool scif_unaligned(off_t src_offset, off_t dst_offset)
{
	src_offset = src_offset & (L1_CACHE_BYTES - 1);
	dst_offset = dst_offset & (L1_CACHE_BYTES - 1);
	return !(src_offset == dst_offset);
}