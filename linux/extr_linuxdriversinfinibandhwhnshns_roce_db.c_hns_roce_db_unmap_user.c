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
struct hns_roce_ucontext {int /*<<< orphan*/  page_mutex; } ;
struct TYPE_3__ {TYPE_2__* user_page; } ;
struct hns_roce_db {TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_if_one (int /*<<< orphan*/ *) ; 

void hns_roce_db_unmap_user(struct hns_roce_ucontext *context,
			    struct hns_roce_db *db)
{
	mutex_lock(&context->page_mutex);

	refcount_dec(&db->u.user_page->refcount);
	if (refcount_dec_if_one(&db->u.user_page->refcount)) {
		list_del(&db->u.user_page->list);
		ib_umem_release(db->u.user_page->umem);
		kfree(db->u.user_page);
	}

	mutex_unlock(&context->page_mutex);
}