#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct pgpath {scalar_t__ is_active; TYPE_2__ path; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_DH_DEV_OFFLINED ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  pg_init_done (struct pgpath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dh_activate (struct request_queue*,int /*<<< orphan*/  (*) (struct pgpath*,int /*<<< orphan*/ ),struct pgpath*) ; 

__attribute__((used)) static void activate_or_offline_path(struct pgpath *pgpath)
{
	struct request_queue *q = bdev_get_queue(pgpath->path.dev->bdev);

	if (pgpath->is_active && !blk_queue_dying(q))
		scsi_dh_activate(q, pg_init_done, pgpath);
	else
		pg_init_done(pgpath, SCSI_DH_DEV_OFFLINED);
}