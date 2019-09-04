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
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  enter_smm_get_segment_flags (struct kvm_segment*) ; 
 int /*<<< orphan*/  kvm_get_segment (struct kvm_vcpu*,struct kvm_segment*,int) ; 
 int /*<<< orphan*/  put_smstate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void enter_smm_save_seg_32(struct kvm_vcpu *vcpu, char *buf, int n)
{
	struct kvm_segment seg;
	int offset;

	kvm_get_segment(vcpu, &seg, n);
	put_smstate(u32, buf, 0x7fa8 + n * 4, seg.selector);

	if (n < 3)
		offset = 0x7f84 + n * 12;
	else
		offset = 0x7f2c + (n - 3) * 12;

	put_smstate(u32, buf, offset + 8, seg.base);
	put_smstate(u32, buf, offset + 4, seg.limit);
	put_smstate(u32, buf, offset, enter_smm_get_segment_flags(&seg));
}