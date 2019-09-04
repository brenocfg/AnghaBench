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
struct kvm_ppc_one_seg_page_size {int page_shift; int slb_enc; TYPE_1__* enc; } ;
struct TYPE_2__ {int page_shift; int pte_enc; } ;

/* Variables and functions */
 void* kvmppc_pgsize_lp_encoding (int,int) ; 

__attribute__((used)) static void kvmppc_add_seg_page_size(struct kvm_ppc_one_seg_page_size **sps,
				     int shift, int sllp)
{
	(*sps)->page_shift = shift;
	(*sps)->slb_enc = sllp;
	(*sps)->enc[0].page_shift = shift;
	(*sps)->enc[0].pte_enc = kvmppc_pgsize_lp_encoding(shift, shift);
	/*
	 * Add 16MB MPSS support (may get filtered out by userspace)
	 */
	if (shift != 24) {
		int penc = kvmppc_pgsize_lp_encoding(shift, 24);
		if (penc != -1) {
			(*sps)->enc[1].page_shift = 24;
			(*sps)->enc[1].pte_enc = penc;
		}
	}
	(*sps)++;
}