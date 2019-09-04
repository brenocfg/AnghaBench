#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cm_work {int /*<<< orphan*/  cm_event; } ;
struct TYPE_4__ {int (* cm_handler ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct cm_id_private {TYPE_1__ id; int /*<<< orphan*/  lock; int /*<<< orphan*/  work_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 struct cm_work* cm_dequeue_work (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_destroy_id (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cm_free_work (struct cm_work*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cm_process_work(struct cm_id_private *cm_id_priv,
			    struct cm_work *work)
{
	int ret;

	/* We will typically only have the current event to report. */
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, &work->cm_event);
	cm_free_work(work);

	while (!ret && !atomic_add_negative(-1, &cm_id_priv->work_count)) {
		spin_lock_irq(&cm_id_priv->lock);
		work = cm_dequeue_work(cm_id_priv);
		spin_unlock_irq(&cm_id_priv->lock);
		if (!work)
			return;

		ret = cm_id_priv->id.cm_handler(&cm_id_priv->id,
						&work->cm_event);
		cm_free_work(work);
	}
	cm_deref_id(cm_id_priv);
	if (ret)
		cm_destroy_id(&cm_id_priv->id, ret);
}