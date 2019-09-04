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
struct kvmppc_xive {int max_sbid; scalar_t__ vp_base; struct kvmppc_xive** src_blocks; int /*<<< orphan*/  dentry; struct kvm* kvm; struct kvmppc_xive* private; } ;
struct kvm_device {int max_sbid; scalar_t__ vp_base; struct kvm_device** src_blocks; int /*<<< orphan*/  dentry; struct kvm* kvm; struct kvm_device* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * xive; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ XIVE_INVALID_VP ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvmppc_xive*) ; 
 int /*<<< orphan*/  kvmppc_xive_free_sources (struct kvmppc_xive*) ; 
 int /*<<< orphan*/  xive_native_free_vp_block (scalar_t__) ; 

__attribute__((used)) static void kvmppc_xive_free(struct kvm_device *dev)
{
	struct kvmppc_xive *xive = dev->private;
	struct kvm *kvm = xive->kvm;
	int i;

	debugfs_remove(xive->dentry);

	if (kvm)
		kvm->arch.xive = NULL;

	/* Mask and free interrupts */
	for (i = 0; i <= xive->max_sbid; i++) {
		if (xive->src_blocks[i])
			kvmppc_xive_free_sources(xive->src_blocks[i]);
		kfree(xive->src_blocks[i]);
		xive->src_blocks[i] = NULL;
	}

	if (xive->vp_base != XIVE_INVALID_VP)
		xive_native_free_vp_block(xive->vp_base);


	kfree(xive);
	kfree(dev);
}