#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {TYPE_4__* dbg; TYPE_1__ uwb_dev; } ;
struct uwb_dbg {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  new_rsv; int /*<<< orphan*/  channel_changed; struct uwb_rc* rc; } ;
struct TYPE_7__ {int /*<<< orphan*/  root_d; void* drp_avail_f; int /*<<< orphan*/  accept; int /*<<< orphan*/  accept_f; void* reservations_f; void* command_f; TYPE_2__ pal; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  rsvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_fops ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,scalar_t__) ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct uwb_rc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drp_avail_fops ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservations_fops ; 
 scalar_t__ root_dir ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dbg_channel_changed ; 
 int /*<<< orphan*/  uwb_dbg_new_rsv ; 
 int /*<<< orphan*/  uwb_pal_init (TYPE_2__*) ; 
 int /*<<< orphan*/  uwb_pal_register (TYPE_2__*) ; 

void uwb_dbg_add_rc(struct uwb_rc *rc)
{
	rc->dbg = kzalloc(sizeof(struct uwb_dbg), GFP_KERNEL);
	if (rc->dbg == NULL)
		return;

	INIT_LIST_HEAD(&rc->dbg->rsvs);
	spin_lock_init(&(rc->dbg)->list_lock);

	uwb_pal_init(&rc->dbg->pal);
	rc->dbg->pal.rc = rc;
	rc->dbg->pal.channel_changed = uwb_dbg_channel_changed;
	rc->dbg->pal.new_rsv = uwb_dbg_new_rsv;
	uwb_pal_register(&rc->dbg->pal);

	if (root_dir) {
		rc->dbg->root_d = debugfs_create_dir(dev_name(&rc->uwb_dev.dev),
						     root_dir);
		rc->dbg->command_f = debugfs_create_file("command", 0200,
							 rc->dbg->root_d, rc,
							 &command_fops);
		rc->dbg->reservations_f = debugfs_create_file("reservations", 0444,
							      rc->dbg->root_d, rc,
							      &reservations_fops);
		rc->dbg->accept_f = debugfs_create_bool("accept", 0644,
							rc->dbg->root_d,
							&rc->dbg->accept);
		rc->dbg->drp_avail_f = debugfs_create_file("drp_avail", 0444,
							   rc->dbg->root_d, rc,
							   &drp_avail_fops);
	}
}