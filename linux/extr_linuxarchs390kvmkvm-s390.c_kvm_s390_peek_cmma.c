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
typedef  unsigned long u8 ;
struct kvm_s390_cmma_log {unsigned long start_gfn; unsigned long count; } ;
struct kvm {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ get_pgste (int /*<<< orphan*/ ,unsigned long,unsigned long*) ; 
 unsigned long gfn_to_hva (struct kvm*,unsigned long) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 

__attribute__((used)) static int kvm_s390_peek_cmma(struct kvm *kvm, struct kvm_s390_cmma_log *args,
			      u8 *res, unsigned long bufsize)
{
	unsigned long pgstev, hva, cur_gfn = args->start_gfn;

	args->count = 0;
	while (args->count < bufsize) {
		hva = gfn_to_hva(kvm, cur_gfn);
		/*
		 * We return an error if the first value was invalid, but we
		 * return successfully if at least one value was copied.
		 */
		if (kvm_is_error_hva(hva))
			return args->count ? 0 : -EFAULT;
		if (get_pgste(kvm->mm, hva, &pgstev) < 0)
			pgstev = 0;
		res[args->count++] = (pgstev >> 24) & 0x43;
		cur_gfn++;
	}

	return 0;
}