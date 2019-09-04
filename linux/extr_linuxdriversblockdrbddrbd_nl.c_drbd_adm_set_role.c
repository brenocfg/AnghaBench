#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct set_role_parms {int /*<<< orphan*/  assume_uptodate; } ;
struct genl_info {TYPE_1__* genlhdr; scalar_t__* attrs; } ;
struct drbd_config_context {TYPE_2__* resource; int /*<<< orphan*/  device; int /*<<< orphan*/  reply_skb; } ;
typedef  int /*<<< orphan*/  parms ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;
struct TYPE_4__ {int /*<<< orphan*/  adm_mutex; } ;
struct TYPE_3__ {scalar_t__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 scalar_t__ DRBD_ADM_PRIMARY ; 
 size_t DRBD_NLA_SET_ROLE_PARMS ; 
 int ERR_MANDATORY_TAG ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  R_PRIMARY ; 
 int /*<<< orphan*/  R_SECONDARY ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_msg_put_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drbd_set_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_attrs_err_to_txt (int) ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int /*<<< orphan*/  memset (struct set_role_parms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_role_parms_from_attrs (struct set_role_parms*,struct genl_info*) ; 

int drbd_adm_set_role(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	struct set_role_parms parms;
	int err;
	enum drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	memset(&parms, 0, sizeof(parms));
	if (info->attrs[DRBD_NLA_SET_ROLE_PARMS]) {
		err = set_role_parms_from_attrs(&parms, info);
		if (err) {
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			goto out;
		}
	}
	genl_unlock();
	mutex_lock(&adm_ctx.resource->adm_mutex);

	if (info->genlhdr->cmd == DRBD_ADM_PRIMARY)
		retcode = drbd_set_role(adm_ctx.device, R_PRIMARY, parms.assume_uptodate);
	else
		retcode = drbd_set_role(adm_ctx.device, R_SECONDARY, 0);

	mutex_unlock(&adm_ctx.resource->adm_mutex);
	genl_lock();
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}