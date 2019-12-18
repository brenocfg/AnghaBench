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
struct uverbs_attr_bundle {struct ib_uverbs_file* ufile; int /*<<< orphan*/  context; } ;
struct ib_uverbs_file {int /*<<< orphan*/  ref; int /*<<< orphan*/  hw_destroy_rwsem; } ;
struct ib_uobject {int /*<<< orphan*/  context; struct ib_uverbs_file* ufile; } ;
struct file {struct ib_uobject* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_REMOVE_CLOSE ; 
 int /*<<< orphan*/  UVERBS_LOOKUP_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_uverbs_release_file ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_destroy_uobject (struct ib_uobject*,int /*<<< orphan*/ ,struct uverbs_attr_bundle*) ; 
 int /*<<< orphan*/  uverbs_try_lock_object (struct ib_uobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uverbs_uobject_put (struct ib_uobject*) ; 

void uverbs_close_fd(struct file *f)
{
	struct ib_uobject *uobj = f->private_data;
	struct ib_uverbs_file *ufile = uobj->ufile;
	struct uverbs_attr_bundle attrs = {
		.context = uobj->context,
		.ufile = ufile,
	};

	if (down_read_trylock(&ufile->hw_destroy_rwsem)) {
		/*
		 * lookup_get_fd_uobject holds the kref on the struct file any
		 * time a FD uobj is locked, which prevents this release
		 * method from being invoked. Meaning we can always get the
		 * write lock here, or we have a kernel bug.
		 */
		WARN_ON(uverbs_try_lock_object(uobj, UVERBS_LOOKUP_WRITE));
		uverbs_destroy_uobject(uobj, RDMA_REMOVE_CLOSE, &attrs);
		up_read(&ufile->hw_destroy_rwsem);
	}

	/* Matches the get in alloc_begin_fd_uobject */
	kref_put(&ufile->ref, ib_uverbs_release_file);

	/* Pairs with filp->private_data in alloc_begin_fd_uobject */
	uverbs_uobject_put(uobj);
}