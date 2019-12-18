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
struct ww_acquire_ctx {int dummy; } ;
struct ttm_validate_buffer {int /*<<< orphan*/ * bo; int /*<<< orphan*/  head; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  ttm_bo_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 

__attribute__((used)) static void
vmw_resource_backoff_reservation(struct ww_acquire_ctx *ticket,
				 struct ttm_validate_buffer *val_buf)
{
	struct list_head val_list;

	if (likely(val_buf->bo == NULL))
		return;

	INIT_LIST_HEAD(&val_list);
	list_add_tail(&val_buf->head, &val_list);
	ttm_eu_backoff_reservation(ticket, &val_list);
	ttm_bo_put(val_buf->bo);
	val_buf->bo = NULL;
}