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
typedef  int u32 ;

/* Variables and functions */
 int IB_FMR_HASH_SIZE ; 
 int jhash_2words (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ib_fmr_hash(u64 first_page)
{
	return jhash_2words((u32) first_page, (u32) (first_page >> 32), 0) &
		(IB_FMR_HASH_SIZE - 1);
}