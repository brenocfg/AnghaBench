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
struct entry_alloc {int dummy; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 unsigned int NR_CACHE_LEVELS ; 
 struct entry* get_entry (struct entry_alloc*,unsigned int) ; 

__attribute__((used)) static struct entry *get_sentinel(struct entry_alloc *ea, unsigned level, bool which)
{
	return get_entry(ea, which ? level : NR_CACHE_LEVELS + level);
}