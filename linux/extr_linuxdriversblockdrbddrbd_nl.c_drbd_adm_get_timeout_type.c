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
struct timeout_parms {int /*<<< orphan*/  timeout_type; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
struct drbd_config_context {int /*<<< orphan*/  reply_skb; TYPE_2__* device; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;
struct TYPE_3__ {scalar_t__ pdsk; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 scalar_t__ D_OUTDATED ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  USE_DEGR_WFC_T ; 
 int /*<<< orphan*/  UT_DEFAULT ; 
 int /*<<< orphan*/  UT_DEGRADED ; 
 int /*<<< orphan*/  UT_PEER_OUTDATED ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int timeout_parms_to_priv_skb (int /*<<< orphan*/ ,struct timeout_parms*) ; 

int drbd_adm_get_timeout_type(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	enum drbd_ret_code retcode;
	struct timeout_parms tp;
	int err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	tp.timeout_type =
		adm_ctx.device->state.pdsk == D_OUTDATED ? UT_PEER_OUTDATED :
		test_bit(USE_DEGR_WFC_T, &adm_ctx.device->flags) ? UT_DEGRADED :
		UT_DEFAULT;

	err = timeout_parms_to_priv_skb(adm_ctx.reply_skb, &tp);
	if (err) {
		nlmsg_free(adm_ctx.reply_skb);
		return err;
	}
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}