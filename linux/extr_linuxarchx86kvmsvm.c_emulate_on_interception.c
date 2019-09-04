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
struct vcpu_svm {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 scalar_t__ EMULATE_DONE ; 
 scalar_t__ kvm_emulate_instruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emulate_on_interception(struct vcpu_svm *svm)
{
	return kvm_emulate_instruction(&svm->vcpu, 0) == EMULATE_DONE;
}