#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct ppl_log {int use_multippl; int entry_space; int wb_cache_on; int /*<<< orphan*/  next_io_sector; TYPE_4__* rdev; TYPE_2__* ppl_conf; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  sector; } ;
struct md_rdev {int /*<<< orphan*/  bdev; TYPE_5__ ppl; } ;
struct TYPE_8__ {int size; } ;
struct TYPE_9__ {TYPE_3__ ppl; } ;
struct TYPE_7__ {TYPE_1__* mddev; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_HAS_MULTIPLE_PPLS ; 
 int PPL_HEADER_SIZE ; 
 int PPL_SPACE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_WC ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppl_init_child_log(struct ppl_log *log, struct md_rdev *rdev)
{
	struct request_queue *q;

	if ((rdev->ppl.size << 9) >= (PPL_SPACE_SIZE +
				      PPL_HEADER_SIZE) * 2) {
		log->use_multippl = true;
		set_bit(MD_HAS_MULTIPLE_PPLS,
			&log->ppl_conf->mddev->flags);
		log->entry_space = PPL_SPACE_SIZE;
	} else {
		log->use_multippl = false;
		log->entry_space = (log->rdev->ppl.size << 9) -
				   PPL_HEADER_SIZE;
	}
	log->next_io_sector = rdev->ppl.sector;

	q = bdev_get_queue(rdev->bdev);
	if (test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		log->wb_cache_on = true;
}