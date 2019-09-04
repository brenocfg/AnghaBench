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
struct tsb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tsb_flush (unsigned long,unsigned long) ; 
 unsigned long tsb_hash (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void __flush_tsb_one_entry(unsigned long tsb, unsigned long v,
				  unsigned long hash_shift,
				  unsigned long nentries)
{
	unsigned long tag, ent, hash;

	v &= ~0x1UL;
	hash = tsb_hash(v, hash_shift, nentries);
	ent = tsb + (hash * sizeof(struct tsb));
	tag = (v >> 22UL);

	tsb_flush(ent, tag);
}