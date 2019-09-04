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
struct kvm_book3e_206_tlb_entry {unsigned int mas1; } ;

/* Variables and functions */
 unsigned int MAS1_TSIZE_MASK ; 
 unsigned int MAS1_TSIZE_SHIFT ; 

__attribute__((used)) static inline unsigned int
get_tlb_tsize(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return (tlbe->mas1 & MAS1_TSIZE_MASK) >> MAS1_TSIZE_SHIFT;
}