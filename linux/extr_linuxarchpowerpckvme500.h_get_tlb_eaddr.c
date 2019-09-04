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
struct kvm_book3e_206_tlb_entry {int mas2; } ;
typedef  int gva_t ;

/* Variables and functions */
 int MAS2_EPN ; 

__attribute__((used)) static inline gva_t get_tlb_eaddr(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return tlbe->mas2 & MAS2_EPN;
}