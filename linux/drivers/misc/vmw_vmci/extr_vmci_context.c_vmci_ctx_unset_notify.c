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
struct vmci_ctx {int /*<<< orphan*/  lock; struct page* notify_page; int /*<<< orphan*/ * notify; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_dummy_notify ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void vmci_ctx_unset_notify(struct vmci_ctx *context)
{
	struct page *notify_page;

	spin_lock(&context->lock);

	notify_page = context->notify_page;
	context->notify = &ctx_dummy_notify;
	context->notify_page = NULL;

	spin_unlock(&context->lock);

	if (notify_page) {
		kunmap(notify_page);
		put_page(notify_page);
	}
}