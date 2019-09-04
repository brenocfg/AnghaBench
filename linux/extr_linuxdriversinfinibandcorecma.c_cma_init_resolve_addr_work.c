#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rdma_id_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event; } ;
struct cma_work {TYPE_1__ event; int /*<<< orphan*/  new_state; int /*<<< orphan*/  old_state; int /*<<< orphan*/  work; struct rdma_id_private* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_CM_ADDR_QUERY ; 
 int /*<<< orphan*/  RDMA_CM_ADDR_RESOLVED ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ADDR_RESOLVED ; 
 int /*<<< orphan*/  cma_work_handler ; 

__attribute__((used)) static void cma_init_resolve_addr_work(struct cma_work *work,
				       struct rdma_id_private *id_priv)
{
	work->id = id_priv;
	INIT_WORK(&work->work, cma_work_handler);
	work->old_state = RDMA_CM_ADDR_QUERY;
	work->new_state = RDMA_CM_ADDR_RESOLVED;
	work->event.event = RDMA_CM_EVENT_ADDR_RESOLVED;
}