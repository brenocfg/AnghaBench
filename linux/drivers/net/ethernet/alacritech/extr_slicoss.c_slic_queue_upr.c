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
struct slic_upr_list {int pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct slic_upr {int /*<<< orphan*/  list; } ;
struct slic_device {struct slic_upr_list upr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slic_start_upr (struct slic_device*,struct slic_upr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slic_queue_upr(struct slic_device *sdev, struct slic_upr *upr)
{
	struct slic_upr_list *upr_list = &sdev->upr_list;
	bool pending;

	spin_lock_bh(&upr_list->lock);
	pending = upr_list->pending;
	INIT_LIST_HEAD(&upr->list);
	list_add_tail(&upr->list, &upr_list->list);
	upr_list->pending = true;
	spin_unlock_bh(&upr_list->lock);

	if (!pending)
		slic_start_upr(sdev, upr);
}