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
struct efa_mmap_entry {scalar_t__ mmap_page; scalar_t__ mmap_flag; } ;

/* Variables and functions */
 int EFA_MMAP_FLAG_SHIFT ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static inline u64 get_mmap_key(const struct efa_mmap_entry *efa)
{
	return ((u64)efa->mmap_flag << EFA_MMAP_FLAG_SHIFT) |
	       ((u64)efa->mmap_page << PAGE_SHIFT);
}