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
struct vmci_handle {scalar_t__ resource; int /*<<< orphan*/  context; } ;
struct vmci_resource {int type; int /*<<< orphan*/  node; struct vmci_handle handle; int /*<<< orphan*/  done; int /*<<< orphan*/  kref; } ;
typedef  enum vmci_resource_type { ____Placeholder_vmci_resource_type } vmci_resource_type ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int VMCI_ERROR_ALREADY_EXISTS ; 
 int VMCI_ERROR_NO_HANDLE ; 
 scalar_t__ VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmci_resource_find_id (int /*<<< orphan*/ ,int) ; 
 unsigned int vmci_resource_hash (struct vmci_handle) ; 
 scalar_t__ vmci_resource_lookup (struct vmci_handle,int) ; 
 TYPE_1__ vmci_resource_table ; 

int vmci_resource_add(struct vmci_resource *resource,
		      enum vmci_resource_type resource_type,
		      struct vmci_handle handle)

{
	unsigned int idx;
	int result;

	spin_lock(&vmci_resource_table.lock);

	if (handle.resource == VMCI_INVALID_ID) {
		handle.resource = vmci_resource_find_id(handle.context,
			resource_type);
		if (handle.resource == VMCI_INVALID_ID) {
			result = VMCI_ERROR_NO_HANDLE;
			goto out;
		}
	} else if (vmci_resource_lookup(handle, resource_type)) {
		result = VMCI_ERROR_ALREADY_EXISTS;
		goto out;
	}

	resource->handle = handle;
	resource->type = resource_type;
	INIT_HLIST_NODE(&resource->node);
	kref_init(&resource->kref);
	init_completion(&resource->done);

	idx = vmci_resource_hash(resource->handle);
	hlist_add_head_rcu(&resource->node, &vmci_resource_table.entries[idx]);

	result = VMCI_SUCCESS;

out:
	spin_unlock(&vmci_resource_table.lock);
	return result;
}