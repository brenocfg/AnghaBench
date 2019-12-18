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
struct work_struct {int dummy; } ;
struct chp_id {int /*<<< orphan*/  id; int /*<<< orphan*/  cssid; } ;
typedef  enum cfg_task_t { ____Placeholder_cfg_task_t } cfg_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  cfg_configure 130 
#define  cfg_deconfigure 129 
 int cfg_get_task (struct chp_id) ; 
 int /*<<< orphan*/  cfg_lock ; 
#define  cfg_none 128 
 int /*<<< orphan*/  cfg_set_task (struct chp_id,int const) ; 
 int /*<<< orphan*/  cfg_wait_queue ; 
 int /*<<< orphan*/  cfg_work ; 
 int chp_cfg_fetch_task (struct chp_id*) ; 
 int /*<<< orphan*/  chsc_chp_offline (struct chp_id) ; 
 int /*<<< orphan*/  chsc_chp_online (struct chp_id) ; 
 int /*<<< orphan*/  info_expire () ; 
 int /*<<< orphan*/  info_update () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int sclp_chp_configure (struct chp_id) ; 
 int sclp_chp_deconfigure (struct chp_id) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfg_func(struct work_struct *work)
{
	struct chp_id chpid;
	enum cfg_task_t t;
	int rc;

	spin_lock(&cfg_lock);
	t = chp_cfg_fetch_task(&chpid);
	spin_unlock(&cfg_lock);

	switch (t) {
	case cfg_configure:
		rc = sclp_chp_configure(chpid);
		if (rc)
			CIO_MSG_EVENT(2, "chp: sclp_chp_configure(%x.%02x)="
				      "%d\n", chpid.cssid, chpid.id, rc);
		else {
			info_expire();
			chsc_chp_online(chpid);
		}
		break;
	case cfg_deconfigure:
		rc = sclp_chp_deconfigure(chpid);
		if (rc)
			CIO_MSG_EVENT(2, "chp: sclp_chp_deconfigure(%x.%02x)="
				      "%d\n", chpid.cssid, chpid.id, rc);
		else {
			info_expire();
			chsc_chp_offline(chpid);
		}
		break;
	case cfg_none:
		/* Get updated information after last change. */
		info_update();
		wake_up_interruptible(&cfg_wait_queue);
		return;
	}
	spin_lock(&cfg_lock);
	if (t == cfg_get_task(chpid))
		cfg_set_task(chpid, cfg_none);
	spin_unlock(&cfg_lock);
	schedule_work(&cfg_work);
}