#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {struct ar9170* priv; } ;
struct TYPE_6__ {int disable_offload_fw; scalar_t__ rx_filter; } ;
struct TYPE_5__ {void* last_slept; void* last_action; } ;
struct ar9170 {int current_factor; int current_density; int usedkeys; int disable_offload; int rx_software_decryption; int /*<<< orphan*/  mutex; TYPE_3__* hw; int /*<<< orphan*/  stat_work; TYPE_2__ fw; int /*<<< orphan*/  mem_allocs; scalar_t__* max_queue_stop_timeout; void** queue_stop_timeout; int /*<<< orphan*/  erp_mode; TYPE_1__ ps; scalar_t__ filter_state; int /*<<< orphan*/ * edcf; } ;
struct TYPE_7__ {int queues; } ;

/* Variables and functions */
 int AR9170_CAM_MAX_USER ; 
 int /*<<< orphan*/  AR9170_DMA_TRIGGER_RXQ ; 
 int /*<<< orphan*/  AR9170_ENC_ALG_NONE ; 
 int /*<<< orphan*/  AR9170_MAC_REG_DMA_TRIGGER ; 
 size_t AR9170_TXQ_BE ; 
 size_t AR9170_TXQ_BK ; 
 size_t AR9170_TXQ_SPECIAL ; 
 size_t AR9170_TXQ_VI ; 
 size_t AR9170_TXQ_VO ; 
 int /*<<< orphan*/  CARL9170_ERP_AUTO ; 
 int /*<<< orphan*/  CARL9170_FILL_QUEUE (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  CARL9170_IDLE ; 
 int CARL9170_RX_FILTER_BAD ; 
 int CARL9170_RX_FILTER_CTL_OTHER ; 
 int CARL9170_RX_FILTER_OTHER_RA ; 
 int /*<<< orphan*/  CARL9170_STARTED ; 
 int /*<<< orphan*/  CARL9170_STAT_WORK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int carl9170_disable_key (struct ar9170*,int) ; 
 int carl9170_init_mac (struct ar9170*) ; 
 int carl9170_rx_filter (struct ar9170*,int) ; 
 int carl9170_set_qos (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_set_state_when (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int carl9170_upload_key (struct ar9170*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int carl9170_usb_open (struct ar9170*) ; 
 int carl9170_write_reg (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_zap_queues (struct ar9170*) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (TYPE_3__*) ; 
 void* jiffies ; 
 int modparam_nohwcrypt ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int carl9170_op_start(struct ieee80211_hw *hw)
{
	struct ar9170 *ar = hw->priv;
	int err, i;

	mutex_lock(&ar->mutex);

	carl9170_zap_queues(ar);

	/* reset QoS defaults */
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_VO], 2, 3,     7, 47);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_VI], 2, 7,    15, 94);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_BE], 3, 15, 1023,  0);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_BK], 7, 15, 1023,  0);
	CARL9170_FILL_QUEUE(ar->edcf[AR9170_TXQ_SPECIAL], 2, 3, 7, 0);

	ar->current_factor = ar->current_density = -1;
	/* "The first key is unique." */
	ar->usedkeys = 1;
	ar->filter_state = 0;
	ar->ps.last_action = jiffies;
	ar->ps.last_slept = jiffies;
	ar->erp_mode = CARL9170_ERP_AUTO;

	/* Set "disable hw crypto offload" whenever the module parameter
	 * nohwcrypt is true or if the firmware does not support it.
	 */
	ar->disable_offload = modparam_nohwcrypt |
		ar->fw.disable_offload_fw;
	ar->rx_software_decryption = ar->disable_offload;

	for (i = 0; i < ar->hw->queues; i++) {
		ar->queue_stop_timeout[i] = jiffies;
		ar->max_queue_stop_timeout[i] = 0;
	}

	atomic_set(&ar->mem_allocs, 0);

	err = carl9170_usb_open(ar);
	if (err)
		goto out;

	err = carl9170_init_mac(ar);
	if (err)
		goto out;

	err = carl9170_set_qos(ar);
	if (err)
		goto out;

	if (ar->fw.rx_filter) {
		err = carl9170_rx_filter(ar, CARL9170_RX_FILTER_OTHER_RA |
			CARL9170_RX_FILTER_CTL_OTHER | CARL9170_RX_FILTER_BAD);
		if (err)
			goto out;
	}

	err = carl9170_write_reg(ar, AR9170_MAC_REG_DMA_TRIGGER,
				 AR9170_DMA_TRIGGER_RXQ);
	if (err)
		goto out;

	/* Clear key-cache */
	for (i = 0; i < AR9170_CAM_MAX_USER + 4; i++) {
		err = carl9170_upload_key(ar, i, NULL, AR9170_ENC_ALG_NONE,
					  0, NULL, 0);
		if (err)
			goto out;

		err = carl9170_upload_key(ar, i, NULL, AR9170_ENC_ALG_NONE,
					  1, NULL, 0);
		if (err)
			goto out;

		if (i < AR9170_CAM_MAX_USER) {
			err = carl9170_disable_key(ar, i);
			if (err)
				goto out;
		}
	}

	carl9170_set_state_when(ar, CARL9170_IDLE, CARL9170_STARTED);

	ieee80211_queue_delayed_work(ar->hw, &ar->stat_work,
		round_jiffies(msecs_to_jiffies(CARL9170_STAT_WORK)));

	ieee80211_wake_queues(ar->hw);
	err = 0;

out:
	mutex_unlock(&ar->mutex);
	return err;
}