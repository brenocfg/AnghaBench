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
struct kfd_dbgdev {TYPE_3__* kq; int /*<<< orphan*/  pqm; } ;
struct TYPE_6__ {TYPE_2__* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_5__ {TYPE_1__ properties; } ;

/* Variables and functions */
 int pqm_destroy_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbgdev_unregister_diq(struct kfd_dbgdev *dbgdev)
{
	/* todo - disable address watch */
	int status;

	status = pqm_destroy_queue(dbgdev->pqm,
			dbgdev->kq->queue->properties.queue_id);
	dbgdev->kq = NULL;

	return status;
}