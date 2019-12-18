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
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  db_drop_task; int /*<<< orphan*/  workq; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4_CONTROL_DB_FULL ; 
 int /*<<< orphan*/  disable_dbs (struct adapter*) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_rdma_uld (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void t4_db_dropped(struct adapter *adap)
{
	if (is_t4(adap->params.chip)) {
		disable_dbs(adap);
		notify_rdma_uld(adap, CXGB4_CONTROL_DB_FULL);
	}
	queue_work(adap->workq, &adap->db_drop_task);
}