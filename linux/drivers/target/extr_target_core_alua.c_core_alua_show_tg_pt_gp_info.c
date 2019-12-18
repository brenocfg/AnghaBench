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
struct config_item {int dummy; } ;
struct TYPE_2__ {struct config_item cg_item; } ;
struct t10_alua_tg_pt_gp {char* tg_pt_gp_id; int /*<<< orphan*/  tg_pt_gp_alua_access_status; int /*<<< orphan*/  tg_pt_gp_alua_access_state; TYPE_1__ tg_pt_gp_group; } ;
struct se_lun {int /*<<< orphan*/  lun_tg_pt_gp_lock; int /*<<< orphan*/  lun_tg_pt_secondary_stat; int /*<<< orphan*/  lun_tg_pt_secondary_offline; struct t10_alua_tg_pt_gp* lun_tg_pt_gp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 char* config_item_name (struct config_item*) ; 
 char* core_alua_dump_state (int /*<<< orphan*/ ) ; 
 char* core_alua_dump_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,char*,char*,char*,char*,char*,char*) ; 

ssize_t core_alua_show_tg_pt_gp_info(struct se_lun *lun, char *page)
{
	struct config_item *tg_pt_ci;
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	ssize_t len = 0;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	if (tg_pt_gp) {
		tg_pt_ci = &tg_pt_gp->tg_pt_gp_group.cg_item;
		len += sprintf(page, "TG Port Alias: %s\nTG Port Group ID:"
			" %hu\nTG Port Primary Access State: %s\nTG Port "
			"Primary Access Status: %s\nTG Port Secondary Access"
			" State: %s\nTG Port Secondary Access Status: %s\n",
			config_item_name(tg_pt_ci), tg_pt_gp->tg_pt_gp_id,
			core_alua_dump_state(
				tg_pt_gp->tg_pt_gp_alua_access_state),
			core_alua_dump_status(
				tg_pt_gp->tg_pt_gp_alua_access_status),
			atomic_read(&lun->lun_tg_pt_secondary_offline) ?
			"Offline" : "None",
			core_alua_dump_status(lun->lun_tg_pt_secondary_stat));
	}
	spin_unlock(&lun->lun_tg_pt_gp_lock);

	return len;
}