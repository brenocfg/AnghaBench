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
struct kvm_htab_ctx {int flags; TYPE_2__* kvm; } ;
struct inode {int dummy; } ;
struct file {struct kvm_htab_ctx* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  hpte_mod_interest; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_GET_HTAB_WRITE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm_htab_ctx*) ; 
 int /*<<< orphan*/  kvm_put_kvm (TYPE_2__*) ; 

__attribute__((used)) static int kvm_htab_release(struct inode *inode, struct file *filp)
{
	struct kvm_htab_ctx *ctx = filp->private_data;

	filp->private_data = NULL;
	if (!(ctx->flags & KVM_GET_HTAB_WRITE))
		atomic_dec(&ctx->kvm->arch.hpte_mod_interest);
	kvm_put_kvm(ctx->kvm);
	kfree(ctx);
	return 0;
}