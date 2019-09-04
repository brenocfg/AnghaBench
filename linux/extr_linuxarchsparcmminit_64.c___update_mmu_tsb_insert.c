#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tsb {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tsb_block; } ;
struct mm_struct {TYPE_2__ context; } ;
struct TYPE_3__ {unsigned long tsb_nentries; struct tsb* tsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  tsb_insert (struct tsb*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __update_mmu_tsb_insert(struct mm_struct *mm, unsigned long tsb_index,
				    unsigned long tsb_hash_shift, unsigned long address,
				    unsigned long tte)
{
	struct tsb *tsb = mm->context.tsb_block[tsb_index].tsb;
	unsigned long tag;

	if (unlikely(!tsb))
		return;

	tsb += ((address >> tsb_hash_shift) &
		(mm->context.tsb_block[tsb_index].tsb_nentries - 1UL));
	tag = (address >> 22UL);
	tsb_insert(tsb, tag, tte);
}