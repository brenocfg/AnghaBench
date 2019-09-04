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
typedef  scalar_t__ vmci_callback ;
typedef  scalar_t__ u32 ;
struct vmci_handle {scalar_t__ context; scalar_t__ resource; } ;
struct dbell_entry {int /*<<< orphan*/  resource; int /*<<< orphan*/  active; scalar_t__ idx; void* client_data; scalar_t__ notify_cb; scalar_t__ run_delayed; int /*<<< orphan*/  work; scalar_t__ priv_flags; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_ERROR_NO_RESOURCES ; 
 scalar_t__ VMCI_FLAG_DELAYED_CB ; 
 scalar_t__ VMCI_HOST_CONTEXT_ID ; 
 scalar_t__ VMCI_INVALID_ID ; 
 scalar_t__ VMCI_PRIVILEGE_ALL_FLAGS ; 
 int /*<<< orphan*/  VMCI_RESOURCE_TYPE_DOORBELL ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dbell_delayed_dispatch ; 
 int /*<<< orphan*/  dbell_index_table_add (struct dbell_entry*) ; 
 int /*<<< orphan*/  dbell_index_table_remove (struct dbell_entry*) ; 
 int dbell_link (struct vmci_handle,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dbell_entry*) ; 
 struct dbell_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 scalar_t__ vmci_get_context_id () ; 
 scalar_t__ vmci_guest_code_active () ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 
 struct vmci_handle vmci_make_handle (scalar_t__,scalar_t__) ; 
 int vmci_resource_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vmci_handle) ; 
 struct vmci_handle vmci_resource_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_resource_remove (int /*<<< orphan*/ *) ; 

int vmci_doorbell_create(struct vmci_handle *handle,
			 u32 flags,
			 u32 priv_flags,
			 vmci_callback notify_cb, void *client_data)
{
	struct dbell_entry *entry;
	struct vmci_handle new_handle;
	int result;

	if (!handle || !notify_cb || flags & ~VMCI_FLAG_DELAYED_CB ||
	    priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS)
		return VMCI_ERROR_INVALID_ARGS;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (entry == NULL) {
		pr_warn("Failed allocating memory for datagram entry\n");
		return VMCI_ERROR_NO_MEM;
	}

	if (vmci_handle_is_invalid(*handle)) {
		u32 context_id = vmci_get_context_id();

		if (context_id == VMCI_INVALID_ID) {
			pr_warn("Failed to get context ID\n");
			result = VMCI_ERROR_NO_RESOURCES;
			goto free_mem;
		}

		/* Let resource code allocate a free ID for us */
		new_handle = vmci_make_handle(context_id, VMCI_INVALID_ID);
	} else {
		bool valid_context = false;

		/*
		 * Validate the handle.  We must do both of the checks below
		 * because we can be acting as both a host and a guest at the
		 * same time. We always allow the host context ID, since the
		 * host functionality is in practice always there with the
		 * unified driver.
		 */
		if (handle->context == VMCI_HOST_CONTEXT_ID ||
		    (vmci_guest_code_active() &&
		     vmci_get_context_id() == handle->context)) {
			valid_context = true;
		}

		if (!valid_context || handle->resource == VMCI_INVALID_ID) {
			pr_devel("Invalid argument (handle=0x%x:0x%x)\n",
				 handle->context, handle->resource);
			result = VMCI_ERROR_INVALID_ARGS;
			goto free_mem;
		}

		new_handle = *handle;
	}

	entry->idx = 0;
	INIT_HLIST_NODE(&entry->node);
	entry->priv_flags = priv_flags;
	INIT_WORK(&entry->work, dbell_delayed_dispatch);
	entry->run_delayed = flags & VMCI_FLAG_DELAYED_CB;
	entry->notify_cb = notify_cb;
	entry->client_data = client_data;
	atomic_set(&entry->active, 0);

	result = vmci_resource_add(&entry->resource,
				   VMCI_RESOURCE_TYPE_DOORBELL,
				   new_handle);
	if (result != VMCI_SUCCESS) {
		pr_warn("Failed to add new resource (handle=0x%x:0x%x), error: %d\n",
			new_handle.context, new_handle.resource, result);
		goto free_mem;
	}

	new_handle = vmci_resource_handle(&entry->resource);
	if (vmci_guest_code_active()) {
		dbell_index_table_add(entry);
		result = dbell_link(new_handle, entry->idx);
		if (VMCI_SUCCESS != result)
			goto destroy_resource;

		atomic_set(&entry->active, 1);
	}

	*handle = new_handle;

	return result;

 destroy_resource:
	dbell_index_table_remove(entry);
	vmci_resource_remove(&entry->resource);
 free_mem:
	kfree(entry);
	return result;
}