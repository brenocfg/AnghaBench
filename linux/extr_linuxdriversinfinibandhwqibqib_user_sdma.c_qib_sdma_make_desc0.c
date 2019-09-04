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
typedef  unsigned long long u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static inline __le64 qib_sdma_make_desc0(u8 gen,
					 u64 addr, u64 dwlen, u64 dwoffset)
{
	return cpu_to_le64(/* SDmaPhyAddr[31:0] */
			   ((addr & 0xfffffffcULL) << 32) |
			   /* SDmaGeneration[1:0] */
			   ((gen & 3ULL) << 30) |
			   /* SDmaDwordCount[10:0] */
			   ((dwlen & 0x7ffULL) << 16) |
			   /* SDmaBufOffset[12:2] */
			   (dwoffset & 0x7ffULL));
}