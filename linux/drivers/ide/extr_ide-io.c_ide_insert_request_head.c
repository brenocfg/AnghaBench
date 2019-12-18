#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  queuelist; } ;
struct TYPE_3__ {int sense_rq_active; int /*<<< orphan*/  rq_work; int /*<<< orphan*/  rq_list; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ide_insert_request_head(ide_drive_t *drive, struct request *rq)
{
	drive->sense_rq_active = true;
	list_add_tail(&rq->queuelist, &drive->rq_list);
	kblockd_schedule_work(&drive->rq_work);
}