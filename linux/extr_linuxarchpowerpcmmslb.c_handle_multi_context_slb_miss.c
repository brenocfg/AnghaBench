#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int get_slice_psize (struct mm_struct*,unsigned long) ; 
 unsigned long get_vsid (int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_slb_entry (unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_highuser_ssize ; 

__attribute__((used)) static void handle_multi_context_slb_miss(int context_id, unsigned long ea)
{
	struct mm_struct *mm = current->mm;
	unsigned long vsid;
	int bpsize;

	/*
	 * We are always above 1TB, hence use high user segment size.
	 */
	vsid = get_vsid(context_id, ea, mmu_highuser_ssize);
	bpsize = get_slice_psize(mm, ea);
	insert_slb_entry(vsid, ea, bpsize, mmu_highuser_ssize);
}