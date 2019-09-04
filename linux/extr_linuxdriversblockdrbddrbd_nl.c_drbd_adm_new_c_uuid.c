#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct new_c_uuid_parms {scalar_t__ clear_bm; } ;
struct genl_info {scalar_t__* attrs; } ;
struct TYPE_12__ {scalar_t__ conn; } ;
struct drbd_device {int /*<<< orphan*/ * state_mutex; TYPE_5__* resource; TYPE_4__ state; TYPE_3__* ldev; } ;
struct drbd_config_context {TYPE_6__* resource; int /*<<< orphan*/  reply_skb; struct drbd_device* device; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_15__ {TYPE_1__* connection; } ;
struct TYPE_14__ {int /*<<< orphan*/  adm_mutex; } ;
struct TYPE_13__ {int /*<<< orphan*/  req_lock; } ;
struct TYPE_10__ {scalar_t__* uuid; } ;
struct TYPE_11__ {TYPE_2__ md; } ;
struct TYPE_9__ {int agreed_pro_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_LOCKED_MASK ; 
 int /*<<< orphan*/  CS_VERBOSE ; 
 scalar_t__ C_CONNECTED ; 
 scalar_t__ C_STANDALONE ; 
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 size_t DRBD_NLA_NEW_C_UUID_PARMS ; 
 int /*<<< orphan*/  D_UP_TO_DATE ; 
 int ERR_CONNECTED ; 
 int ERR_IO_MD_DISK ; 
 int ERR_MANDATORY_TAG ; 
 int ERR_NO_DISK ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  UI_BITMAP ; 
 size_t UI_CURRENT ; 
 scalar_t__ UUID_JUST_CREATED ; 
 int /*<<< orphan*/  _NS2 (struct drbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drbd_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drbd_uuid_set (struct drbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int drbd_bitmap_io (struct drbd_device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_bmio_clear_n_write ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,int) ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  drbd_md_sync (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_msg_put_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_print_uuids (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  drbd_send_uuids_skip_initial_sync (TYPE_7__*) ; 
 int /*<<< orphan*/  drbd_uuid_new_current (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_uuid_set (struct drbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  from_attrs_err_to_txt (int) ; 
 int /*<<< orphan*/  get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  memset (struct new_c_uuid_parms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int new_c_uuid_parms_from_attrs (struct new_c_uuid_parms*,struct genl_info*) ; 
 int /*<<< orphan*/  pdsk ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int drbd_adm_new_c_uuid(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	struct drbd_device *device;
	enum drbd_ret_code retcode;
	int skip_initial_sync = 0;
	int err;
	struct new_c_uuid_parms args;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out_nolock;

	device = adm_ctx.device;
	memset(&args, 0, sizeof(args));
	if (info->attrs[DRBD_NLA_NEW_C_UUID_PARMS]) {
		err = new_c_uuid_parms_from_attrs(&args, info);
		if (err) {
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			goto out_nolock;
		}
	}

	mutex_lock(&adm_ctx.resource->adm_mutex);
	mutex_lock(device->state_mutex); /* Protects us against serialized state changes. */

	if (!get_ldev(device)) {
		retcode = ERR_NO_DISK;
		goto out;
	}

	/* this is "skip initial sync", assume to be clean */
	if (device->state.conn == C_CONNECTED &&
	    first_peer_device(device)->connection->agreed_pro_version >= 90 &&
	    device->ldev->md.uuid[UI_CURRENT] == UUID_JUST_CREATED && args.clear_bm) {
		drbd_info(device, "Preparing to skip initial sync\n");
		skip_initial_sync = 1;
	} else if (device->state.conn != C_STANDALONE) {
		retcode = ERR_CONNECTED;
		goto out_dec;
	}

	drbd_uuid_set(device, UI_BITMAP, 0); /* Rotate UI_BITMAP to History 1, etc... */
	drbd_uuid_new_current(device); /* New current, previous to UI_BITMAP */

	if (args.clear_bm) {
		err = drbd_bitmap_io(device, &drbd_bmio_clear_n_write,
			"clear_n_write from new_c_uuid", BM_LOCKED_MASK);
		if (err) {
			drbd_err(device, "Writing bitmap failed with %d\n", err);
			retcode = ERR_IO_MD_DISK;
		}
		if (skip_initial_sync) {
			drbd_send_uuids_skip_initial_sync(first_peer_device(device));
			_drbd_uuid_set(device, UI_BITMAP, 0);
			drbd_print_uuids(device, "cleared bitmap UUID");
			spin_lock_irq(&device->resource->req_lock);
			_drbd_set_state(_NS2(device, disk, D_UP_TO_DATE, pdsk, D_UP_TO_DATE),
					CS_VERBOSE, NULL);
			spin_unlock_irq(&device->resource->req_lock);
		}
	}

	drbd_md_sync(device);
out_dec:
	put_ldev(device);
out:
	mutex_unlock(device->state_mutex);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out_nolock:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}