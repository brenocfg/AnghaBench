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
typedef  int /*<<< orphan*/  u16 ;
struct efa_com_admin_queue {size_t comp_ctx_pool_next; int /*<<< orphan*/  comp_ctx_lock; int /*<<< orphan*/ * comp_ctx_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 efa_com_alloc_ctx_id(struct efa_com_admin_queue *aq)
{
	u16 ctx_id;

	spin_lock(&aq->comp_ctx_lock);
	ctx_id = aq->comp_ctx_pool[aq->comp_ctx_pool_next];
	aq->comp_ctx_pool_next++;
	spin_unlock(&aq->comp_ctx_lock);

	return ctx_id;
}