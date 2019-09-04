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
struct TYPE_2__ {int /*<<< orphan*/ * sca; scalar_t__ use_esca; } ;
struct kvm {TYPE_1__ arch; } ;
struct esca_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sca_dispose(struct kvm *kvm)
{
	if (kvm->arch.use_esca)
		free_pages_exact(kvm->arch.sca, sizeof(struct esca_block));
	else
		free_page((unsigned long)(kvm->arch.sca));
	kvm->arch.sca = NULL;
}