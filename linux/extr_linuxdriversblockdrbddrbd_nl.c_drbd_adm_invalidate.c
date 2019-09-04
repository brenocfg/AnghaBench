#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
struct TYPE_6__ {scalar_t__ conn; scalar_t__ role; } ;
struct drbd_device {TYPE_2__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  misc_wait; } ;
struct drbd_config_context {TYPE_3__* resource; struct drbd_device* device; int /*<<< orphan*/  reply_skb; } ;
struct TYPE_8__ {TYPE_1__* connection; } ;
struct TYPE_7__ {int /*<<< orphan*/  adm_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  sender_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_IO ; 
 int /*<<< orphan*/  BM_LOCKED_MASK ; 
 scalar_t__ C_STANDALONE ; 
 int /*<<< orphan*/  C_STARTING_SYNC_T ; 
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 int /*<<< orphan*/  D_INCONSISTENT ; 
 int ERR_IO_MD_DISK ; 
 int ERR_NO_DISK ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ R_SECONDARY ; 
 int SS_SUCCESS ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ drbd_bitmap_io (struct drbd_device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_bmio_set_n_write ; 
 int /*<<< orphan*/  drbd_flush_workqueue (int /*<<< orphan*/ *) ; 
 int drbd_request_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_resume_io (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_suspend_io (struct drbd_device*) ; 
 TYPE_4__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int drbd_adm_invalidate(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	struct drbd_device *device;
	int retcode; /* enum drbd_ret_code rsp. enum drbd_state_rv */

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	device = adm_ctx.device;
	if (!get_ldev(device)) {
		retcode = ERR_NO_DISK;
		goto out;
	}

	mutex_lock(&adm_ctx.resource->adm_mutex);

	/* If there is still bitmap IO pending, probably because of a previous
	 * resync just being finished, wait for it before requesting a new resync.
	 * Also wait for it's after_state_ch(). */
	drbd_suspend_io(device);
	wait_event(device->misc_wait, !test_bit(BITMAP_IO, &device->flags));
	drbd_flush_workqueue(&first_peer_device(device)->connection->sender_work);

	/* If we happen to be C_STANDALONE R_SECONDARY, just change to
	 * D_INCONSISTENT, and set all bits in the bitmap.  Otherwise,
	 * try to start a resync handshake as sync target for full sync.
	 */
	if (device->state.conn == C_STANDALONE && device->state.role == R_SECONDARY) {
		retcode = drbd_request_state(device, NS(disk, D_INCONSISTENT));
		if (retcode >= SS_SUCCESS) {
			if (drbd_bitmap_io(device, &drbd_bmio_set_n_write,
				"set_n_write from invalidate", BM_LOCKED_MASK))
				retcode = ERR_IO_MD_DISK;
		}
	} else
		retcode = drbd_request_state(device, NS(conn, C_STARTING_SYNC_T));
	drbd_resume_io(device);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
	put_ldev(device);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}