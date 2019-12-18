#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qed_ptt_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; TYPE_3__* ptts; } ;
struct qed_hwfn {struct qed_ptt_pool* p_ptt_pool; int /*<<< orphan*/  my_id; } ;
struct TYPE_4__ {scalar_t__ control; } ;
struct TYPE_5__ {TYPE_1__ pretend; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int idx; int /*<<< orphan*/  list_entry; int /*<<< orphan*/  hwfn_id; TYPE_2__ pxp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PXP_EXTERNAL_BAR_PF_WINDOW_NUM ; 
 int /*<<< orphan*/  QED_BAR_INVALID_OFFSET ; 
 int RESERVED_PTT_MAX ; 
 struct qed_ptt_pool* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qed_ptt_pool_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_ptt_pool *p_pool = kmalloc(sizeof(*p_pool), GFP_KERNEL);
	int i;

	if (!p_pool)
		return -ENOMEM;

	INIT_LIST_HEAD(&p_pool->free_list);
	for (i = 0; i < PXP_EXTERNAL_BAR_PF_WINDOW_NUM; i++) {
		p_pool->ptts[i].idx = i;
		p_pool->ptts[i].pxp.offset = QED_BAR_INVALID_OFFSET;
		p_pool->ptts[i].pxp.pretend.control = 0;
		p_pool->ptts[i].hwfn_id = p_hwfn->my_id;
		if (i >= RESERVED_PTT_MAX)
			list_add(&p_pool->ptts[i].list_entry,
				 &p_pool->free_list);
	}

	p_hwfn->p_ptt_pool = p_pool;
	spin_lock_init(&p_pool->lock);

	return 0;
}