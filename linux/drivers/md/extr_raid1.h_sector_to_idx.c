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
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER_BUCKETS_NR_BITS ; 
 int BARRIER_UNIT_SECTOR_BITS ; 
 int hash_long (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sector_to_idx(sector_t sector)
{
	return hash_long(sector >> BARRIER_UNIT_SECTOR_BITS,
			 BARRIER_BUCKETS_NR_BITS);
}