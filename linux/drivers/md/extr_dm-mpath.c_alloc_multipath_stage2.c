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
struct multipath {scalar_t__ queue_mode; int /*<<< orphan*/  pg_init_wait; int /*<<< orphan*/  pg_init_delay_msecs; int /*<<< orphan*/  pg_init_count; int /*<<< orphan*/  pg_init_in_progress; int /*<<< orphan*/  flags; int /*<<< orphan*/  process_queued_bios; } ;
struct dm_target {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_PG_INIT_DELAY_DEFAULT ; 
 scalar_t__ DM_TYPE_BIO_BASED ; 
 scalar_t__ DM_TYPE_NONE ; 
 scalar_t__ DM_TYPE_REQUEST_BASED ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IO ; 
 int /*<<< orphan*/  MPATHF_RETAIN_ATTACHED_HW_HANDLER ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_set_type (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_queued_bios ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_multipath_stage2(struct dm_target *ti, struct multipath *m)
{
	if (m->queue_mode == DM_TYPE_NONE) {
		m->queue_mode = DM_TYPE_REQUEST_BASED;
	} else if (m->queue_mode == DM_TYPE_BIO_BASED) {
		INIT_WORK(&m->process_queued_bios, process_queued_bios);
		/*
		 * bio-based doesn't support any direct scsi_dh management;
		 * it just discovers if a scsi_dh is attached.
		 */
		set_bit(MPATHF_RETAIN_ATTACHED_HW_HANDLER, &m->flags);
	}

	dm_table_set_type(ti->table, m->queue_mode);

	/*
	 * Init fields that are only used when a scsi_dh is attached
	 * - must do this unconditionally (really doesn't hurt non-SCSI uses)
	 */
	set_bit(MPATHF_QUEUE_IO, &m->flags);
	atomic_set(&m->pg_init_in_progress, 0);
	atomic_set(&m->pg_init_count, 0);
	m->pg_init_delay_msecs = DM_PG_INIT_DELAY_DEFAULT;
	init_waitqueue_head(&m->pg_init_wait);

	return 0;
}