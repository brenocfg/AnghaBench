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
struct dm_integrity_c {int* commit_ids; } ;
typedef  int commit_id_t ;
typedef  int __u64 ;

/* Variables and functions */
 int cpu_to_le64 (int) ; 

__attribute__((used)) static commit_id_t dm_integrity_commit_id(struct dm_integrity_c *ic, unsigned i,
					  unsigned j, unsigned char seq)
{
	/*
	 * Xor the number with section and sector, so that if a piece of
	 * journal is written at wrong place, it is detected.
	 */
	return ic->commit_ids[seq] ^ cpu_to_le64(((__u64)i << 32) ^ j);
}