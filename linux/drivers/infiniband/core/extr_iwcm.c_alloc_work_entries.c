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
struct iwcm_work {int /*<<< orphan*/  list; struct iwcm_id_private* cm_id; } ;
struct iwcm_id_private {int /*<<< orphan*/  work_free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dealloc_work_entries (struct iwcm_id_private*) ; 
 struct iwcm_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_work (struct iwcm_work*) ; 

__attribute__((used)) static int alloc_work_entries(struct iwcm_id_private *cm_id_priv, int count)
{
	struct iwcm_work *work;

	BUG_ON(!list_empty(&cm_id_priv->work_free_list));
	while (count--) {
		work = kmalloc(sizeof(struct iwcm_work), GFP_KERNEL);
		if (!work) {
			dealloc_work_entries(cm_id_priv);
			return -ENOMEM;
		}
		work->cm_id = cm_id_priv;
		INIT_LIST_HEAD(&work->list);
		put_work(work);
	}
	return 0;
}