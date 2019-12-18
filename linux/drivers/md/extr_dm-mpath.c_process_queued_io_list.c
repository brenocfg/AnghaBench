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
struct multipath {scalar_t__ queue_mode; int /*<<< orphan*/  process_queued_bios; TYPE_1__* ti; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 scalar_t__ DM_TYPE_BIO_BASED ; 
 scalar_t__ DM_TYPE_REQUEST_BASED ; 
 int /*<<< orphan*/  dm_mq_kick_requeue_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_get_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmultipathd ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_queued_io_list(struct multipath *m)
{
	if (m->queue_mode == DM_TYPE_REQUEST_BASED)
		dm_mq_kick_requeue_list(dm_table_get_md(m->ti->table));
	else if (m->queue_mode == DM_TYPE_BIO_BASED)
		queue_work(kmultipathd, &m->process_queued_bios);
}