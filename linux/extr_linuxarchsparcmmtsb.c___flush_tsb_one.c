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
struct tlb_batch {unsigned long tlb_nr; int /*<<< orphan*/ * vaddrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tsb_one_entry (unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static void __flush_tsb_one(struct tlb_batch *tb, unsigned long hash_shift,
			    unsigned long tsb, unsigned long nentries)
{
	unsigned long i;

	for (i = 0; i < tb->tlb_nr; i++)
		__flush_tsb_one_entry(tsb, tb->vaddrs[i], hash_shift, nentries);
}