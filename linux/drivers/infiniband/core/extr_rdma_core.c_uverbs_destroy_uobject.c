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
struct uverbs_attr_bundle {struct ib_uverbs_file* ufile; } ;
struct ib_uverbs_file {int /*<<< orphan*/  uobjects_lock; int /*<<< orphan*/  hw_destroy_rwsem; } ;
struct ib_uobject {int /*<<< orphan*/  list; TYPE_2__* uapi_object; int /*<<< orphan*/  usecnt; int /*<<< orphan*/ * context; int /*<<< orphan*/ * object; int /*<<< orphan*/  id; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_4__ {TYPE_1__* type_class; } ;
struct TYPE_3__ {int (* destroy_hw ) (struct ib_uobject*,int,struct uverbs_attr_bundle*) ;int /*<<< orphan*/  (* remove_handle ) (struct ib_uobject*) ;int /*<<< orphan*/  (* alloc_abort ) (struct ib_uobject*) ;} ;

/* Variables and functions */
 int RDMA_REMOVE_ABORT ; 
 int RDMA_REMOVE_DESTROY ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_WRITE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_uverbs_usecnt (struct ib_uobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_is_destroy_retryable (int,int,struct ib_uobject*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct ib_uobject*,int,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  stub2 (struct ib_uobject*) ; 
 int /*<<< orphan*/  stub3 (struct ib_uobject*) ; 
 int /*<<< orphan*/  uverbs_uobject_put (struct ib_uobject*) ; 

__attribute__((used)) static int uverbs_destroy_uobject(struct ib_uobject *uobj,
				  enum rdma_remove_reason reason,
				  struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_file *ufile = attrs->ufile;
	unsigned long flags;
	int ret;

	lockdep_assert_held(&ufile->hw_destroy_rwsem);
	assert_uverbs_usecnt(uobj, UVERBS_LOOKUP_WRITE);

	if (uobj->object) {
		ret = uobj->uapi_object->type_class->destroy_hw(uobj, reason,
								attrs);
		if (ret) {
			if (ib_is_destroy_retryable(ret, reason, uobj))
				return ret;

			/* Nothing to be done, dangle the memory and move on */
			WARN(true,
			     "ib_uverbs: failed to remove uobject id %d, driver err=%d",
			     uobj->id, ret);
		}

		uobj->object = NULL;
	}

	if (reason == RDMA_REMOVE_ABORT) {
		WARN_ON(!list_empty(&uobj->list));
		WARN_ON(!uobj->context);
		uobj->uapi_object->type_class->alloc_abort(uobj);
	}

	uobj->context = NULL;

	/*
	 * For DESTROY the usecnt is held write locked, the caller is expected
	 * to put it unlock and put the object when done with it. Only DESTROY
	 * can remove the IDR handle.
	 */
	if (reason != RDMA_REMOVE_DESTROY)
		atomic_set(&uobj->usecnt, 0);
	else
		uobj->uapi_object->type_class->remove_handle(uobj);

	if (!list_empty(&uobj->list)) {
		spin_lock_irqsave(&ufile->uobjects_lock, flags);
		list_del_init(&uobj->list);
		spin_unlock_irqrestore(&ufile->uobjects_lock, flags);

		/*
		 * Pairs with the get in rdma_alloc_commit_uobject(), could
		 * destroy uobj.
		 */
		uverbs_uobject_put(uobj);
	}

	/*
	 * When aborting the stack kref remains owned by the core code, and is
	 * not transferred into the type. Pairs with the get in alloc_uobj
	 */
	if (reason == RDMA_REMOVE_ABORT)
		uverbs_uobject_put(uobj);

	return 0;
}