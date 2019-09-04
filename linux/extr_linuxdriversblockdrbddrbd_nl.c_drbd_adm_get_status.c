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
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
struct drbd_config_context {int /*<<< orphan*/  reply_skb; int /*<<< orphan*/  device; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int nla_put_status_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsg_free (int /*<<< orphan*/ ) ; 

int drbd_adm_get_status(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	enum drbd_ret_code retcode;
	int err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	err = nla_put_status_info(adm_ctx.reply_skb, adm_ctx.device, NULL);
	if (err) {
		nlmsg_free(adm_ctx.reply_skb);
		return err;
	}
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}