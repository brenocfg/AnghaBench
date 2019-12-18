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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  wait_queue; } ;
struct vmci_ctx {int user_version; void* queue_pair_array; void* doorbell_array; int /*<<< orphan*/  list_item; scalar_t__ cid; int /*<<< orphan*/ * notify_page; int /*<<< orphan*/ * notify; int /*<<< orphan*/  cred; scalar_t__ priv_flags; void* pending_doorbell_array; TYPE_1__ host_context; int /*<<< orphan*/  notifier_list; int /*<<< orphan*/  datagram_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  kref; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct vmci_ctx* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ VMCI_INVALID_ID ; 
 int /*<<< orphan*/  VMCI_MAX_GUEST_DOORBELL_COUNT ; 
 int /*<<< orphan*/  VMCI_MAX_GUEST_QP_COUNT ; 
 scalar_t__ VMCI_PRIVILEGE_ALL_FLAGS ; 
 scalar_t__ VMCI_RESERVED_CID_LIMIT ; 
 int /*<<< orphan*/  ctx_dummy_notify ; 
 TYPE_2__ ctx_list ; 
 int /*<<< orphan*/  get_cred (struct cred const*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmci_ctx*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct vmci_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmci_ctx_exists (scalar_t__) ; 
 void* vmci_handle_arr_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_handle_arr_destroy (void*) ; 

struct vmci_ctx *vmci_ctx_create(u32 cid, u32 priv_flags,
				 uintptr_t event_hnd,
				 int user_version,
				 const struct cred *cred)
{
	struct vmci_ctx *context;
	int error;

	if (cid == VMCI_INVALID_ID) {
		pr_devel("Invalid context ID for VMCI context\n");
		error = -EINVAL;
		goto err_out;
	}

	if (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS) {
		pr_devel("Invalid flag (flags=0x%x) for VMCI context\n",
			 priv_flags);
		error = -EINVAL;
		goto err_out;
	}

	if (user_version == 0) {
		pr_devel("Invalid suer_version %d\n", user_version);
		error = -EINVAL;
		goto err_out;
	}

	context = kzalloc(sizeof(*context), GFP_KERNEL);
	if (!context) {
		pr_warn("Failed to allocate memory for VMCI context\n");
		error = -EINVAL;
		goto err_out;
	}

	kref_init(&context->kref);
	spin_lock_init(&context->lock);
	INIT_LIST_HEAD(&context->list_item);
	INIT_LIST_HEAD(&context->datagram_queue);
	INIT_LIST_HEAD(&context->notifier_list);

	/* Initialize host-specific VMCI context. */
	init_waitqueue_head(&context->host_context.wait_queue);

	context->queue_pair_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_QP_COUNT);
	if (!context->queue_pair_array) {
		error = -ENOMEM;
		goto err_free_ctx;
	}

	context->doorbell_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_DOORBELL_COUNT);
	if (!context->doorbell_array) {
		error = -ENOMEM;
		goto err_free_qp_array;
	}

	context->pending_doorbell_array =
		vmci_handle_arr_create(0, VMCI_MAX_GUEST_DOORBELL_COUNT);
	if (!context->pending_doorbell_array) {
		error = -ENOMEM;
		goto err_free_db_array;
	}

	context->user_version = user_version;

	context->priv_flags = priv_flags;

	if (cred)
		context->cred = get_cred(cred);

	context->notify = &ctx_dummy_notify;
	context->notify_page = NULL;

	/*
	 * If we collide with an existing context we generate a new
	 * and use it instead. The VMX will determine if regeneration
	 * is okay. Since there isn't 4B - 16 VMs running on a given
	 * host, the below loop will terminate.
	 */
	spin_lock(&ctx_list.lock);

	while (vmci_ctx_exists(cid)) {
		/* We reserve the lowest 16 ids for fixed contexts. */
		cid = max(cid, VMCI_RESERVED_CID_LIMIT - 1) + 1;
		if (cid == VMCI_INVALID_ID)
			cid = VMCI_RESERVED_CID_LIMIT;
	}
	context->cid = cid;

	list_add_tail_rcu(&context->list_item, &ctx_list.head);
	spin_unlock(&ctx_list.lock);

	return context;

 err_free_db_array:
	vmci_handle_arr_destroy(context->doorbell_array);
 err_free_qp_array:
	vmci_handle_arr_destroy(context->queue_pair_array);
 err_free_ctx:
	kfree(context);
 err_out:
	return ERR_PTR(error);
}