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
struct kvmgt_guest_info {int /*<<< orphan*/  vgpu; int /*<<< orphan*/  kvm; int /*<<< orphan*/  track_node; int /*<<< orphan*/  debugfs_cache_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_page_track_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_put_kvm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmgt_protect_table_destroy (struct kvmgt_guest_info*) ; 
 int /*<<< orphan*/  vfree (struct kvmgt_guest_info*) ; 

__attribute__((used)) static bool kvmgt_guest_exit(struct kvmgt_guest_info *info)
{
	debugfs_remove(info->debugfs_cache_entries);

	kvm_page_track_unregister_notifier(info->kvm, &info->track_node);
	kvm_put_kvm(info->kvm);
	kvmgt_protect_table_destroy(info);
	gvt_cache_destroy(info->vgpu);
	vfree(info);

	return true;
}