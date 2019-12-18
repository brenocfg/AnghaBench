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
struct rtllib_device {int /*<<< orphan*/  ps_task; int /*<<< orphan*/  wx_mutex; int /*<<< orphan*/  wx_sync_scan_wq; int /*<<< orphan*/  ips_leave_wq; int /*<<< orphan*/  associate_complete_wq; int /*<<< orphan*/  link_change_wq; int /*<<< orphan*/  hw_sleep_wq; int /*<<< orphan*/  hw_wakeup_wq; int /*<<< orphan*/  start_ibss_wq; int /*<<< orphan*/  softmac_scan_wq; int /*<<< orphan*/  associate_procedure_wq; int /*<<< orphan*/  associate_retry_wq; int /*<<< orphan*/  associate_timer; int /*<<< orphan*/ * dot11d_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void rtllib_softmac_free(struct rtllib_device *ieee)
{
	mutex_lock(&ieee->wx_mutex);
	kfree(ieee->dot11d_info);
	ieee->dot11d_info = NULL;
	del_timer_sync(&ieee->associate_timer);

	cancel_delayed_work_sync(&ieee->associate_retry_wq);
	cancel_delayed_work_sync(&ieee->associate_procedure_wq);
	cancel_delayed_work_sync(&ieee->softmac_scan_wq);
	cancel_delayed_work_sync(&ieee->start_ibss_wq);
	cancel_delayed_work_sync(&ieee->hw_wakeup_wq);
	cancel_delayed_work_sync(&ieee->hw_sleep_wq);
	cancel_delayed_work_sync(&ieee->link_change_wq);
	cancel_work_sync(&ieee->associate_complete_wq);
	cancel_work_sync(&ieee->ips_leave_wq);
	cancel_work_sync(&ieee->wx_sync_scan_wq);
	mutex_unlock(&ieee->wx_mutex);
	tasklet_kill(&ieee->ps_task);
}