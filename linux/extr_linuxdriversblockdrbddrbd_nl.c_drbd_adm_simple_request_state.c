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
typedef  union drbd_state {int dummy; } drbd_state ;
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
struct drbd_config_context {TYPE_1__* resource; int /*<<< orphan*/  device; int /*<<< orphan*/  reply_skb; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;
struct TYPE_2__ {int /*<<< orphan*/  adm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int drbd_request_state (int /*<<< orphan*/ ,union drbd_state,union drbd_state) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbd_adm_simple_request_state(struct sk_buff *skb, struct genl_info *info,
		union drbd_state mask, union drbd_state val)
{
	struct drbd_config_context adm_ctx;
	enum drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	retcode = drbd_request_state(adm_ctx.device, mask, val);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}