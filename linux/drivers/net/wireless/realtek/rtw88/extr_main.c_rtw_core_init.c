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
struct TYPE_9__ {int current_channel; int rcr; int /*<<< orphan*/  tx_power_mutex; } ;
struct TYPE_8__ {int total_cam_num; } ;
struct rtw_coex {int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; int /*<<< orphan*/  defreeze_work; int /*<<< orphan*/  bt_reenable_work; int /*<<< orphan*/  bt_relink_work; } ;
struct TYPE_7__ {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  purge_timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct rtw_dev {TYPE_5__* chip; TYPE_4__ hal; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mac_id_map; TYPE_3__ sec; struct rtw_coex coex; TYPE_2__ tx_report; TYPE_1__ h2c; int /*<<< orphan*/  rf_lock; int /*<<< orphan*/  dm_lock; int /*<<< orphan*/  c2h_queue; int /*<<< orphan*/  c2h_work; int /*<<< orphan*/  lps_work; int /*<<< orphan*/  watch_dog_work; int /*<<< orphan*/  rsvd_page_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  fw_name; } ;

/* Variables and functions */
 int BIT_AB ; 
 int BIT_AM ; 
 int BIT_APM ; 
 int BIT_APP_FCS ; 
 int BIT_APP_ICV ; 
 int BIT_APP_MIC ; 
 int BIT_APP_PHYSTS ; 
 int BIT_HTC_LOC_CTRL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSVD_BEACON ; 
 int /*<<< orphan*/  RTW_BC_MC_MACID ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_add_rsvd_page (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_c2h_work ; 
 int /*<<< orphan*/  rtw_coex_bt_reenable_work ; 
 int /*<<< orphan*/  rtw_coex_bt_relink_work ; 
 int /*<<< orphan*/  rtw_coex_defreeze_work ; 
 int rtw_load_firmware (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_lps_work ; 
 int /*<<< orphan*/  rtw_tx_report_purge_timer ; 
 int /*<<< orphan*/  rtw_warn (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_watch_dog_work ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_core_init(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	int ret;

	INIT_LIST_HEAD(&rtwdev->rsvd_page_list);

	timer_setup(&rtwdev->tx_report.purge_timer,
		    rtw_tx_report_purge_timer, 0);

	INIT_DELAYED_WORK(&rtwdev->watch_dog_work, rtw_watch_dog_work);
	INIT_DELAYED_WORK(&rtwdev->lps_work, rtw_lps_work);
	INIT_DELAYED_WORK(&coex->bt_relink_work, rtw_coex_bt_relink_work);
	INIT_DELAYED_WORK(&coex->bt_reenable_work, rtw_coex_bt_reenable_work);
	INIT_DELAYED_WORK(&coex->defreeze_work, rtw_coex_defreeze_work);
	INIT_WORK(&rtwdev->c2h_work, rtw_c2h_work);
	skb_queue_head_init(&rtwdev->c2h_queue);
	skb_queue_head_init(&rtwdev->coex.queue);
	skb_queue_head_init(&rtwdev->tx_report.queue);

	spin_lock_init(&rtwdev->dm_lock);
	spin_lock_init(&rtwdev->rf_lock);
	spin_lock_init(&rtwdev->h2c.lock);
	spin_lock_init(&rtwdev->tx_report.q_lock);

	mutex_init(&rtwdev->mutex);
	mutex_init(&rtwdev->coex.mutex);
	mutex_init(&rtwdev->hal.tx_power_mutex);

	init_waitqueue_head(&rtwdev->coex.wait);

	rtwdev->sec.total_cam_num = 32;
	rtwdev->hal.current_channel = 1;
	set_bit(RTW_BC_MC_MACID, rtwdev->mac_id_map);

	mutex_lock(&rtwdev->mutex);
	rtw_add_rsvd_page(rtwdev, RSVD_BEACON, false);
	mutex_unlock(&rtwdev->mutex);

	/* default rx filter setting */
	rtwdev->hal.rcr = BIT_APP_FCS | BIT_APP_MIC | BIT_APP_ICV |
			  BIT_HTC_LOC_CTRL | BIT_APP_PHYSTS |
			  BIT_AB | BIT_AM | BIT_APM;

	ret = rtw_load_firmware(rtwdev, rtwdev->chip->fw_name);
	if (ret) {
		rtw_warn(rtwdev, "no firmware loaded\n");
		return ret;
	}

	return 0;
}