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
struct sk_buff {int dummy; } ;
struct resource_info {int dummy; } ;
struct res_opts {int dummy; } ;
struct genl_info {TYPE_1__* nlhdr; } ;
struct drbd_connection {int /*<<< orphan*/  resource; } ;
struct drbd_config_context {int /*<<< orphan*/  resource_name; int /*<<< orphan*/  reply_skb; scalar_t__ resource; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;
struct TYPE_2__ {int nlmsg_flags; } ;

/* Variables and functions */
 int ENOMSG ; 
 int ERR_INVALID_REQUEST ; 
 int ERR_MANDATORY_TAG ; 
 int ERR_NOMEM ; 
 int NLM_F_EXCL ; 
 int /*<<< orphan*/  NOTIFY_CREATE ; 
 int NO_ERROR ; 
 struct drbd_connection* conn_create (int /*<<< orphan*/ ,struct res_opts*) ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int drbd_check_resource_name (struct drbd_config_context*) ; 
 int /*<<< orphan*/  drbd_msg_put_info (int /*<<< orphan*/ ,char*) ; 
 char* from_attrs_err_to_txt (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notification_mutex ; 
 int /*<<< orphan*/  notify_resource_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_info*,int /*<<< orphan*/ ) ; 
 int res_opts_from_attrs (struct res_opts*,struct genl_info*) ; 
 int /*<<< orphan*/  resource_to_info (struct resource_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resources_mutex ; 
 int /*<<< orphan*/  set_res_opts_defaults (struct res_opts*) ; 

int drbd_adm_new_resource(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_connection *connection;
	struct drbd_config_context adm_ctx;
	enum drbd_ret_code retcode;
	struct res_opts res_opts;
	int err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, 0);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	set_res_opts_defaults(&res_opts);
	err = res_opts_from_attrs(&res_opts, info);
	if (err && err != -ENOMSG) {
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		goto out;
	}

	retcode = drbd_check_resource_name(&adm_ctx);
	if (retcode != NO_ERROR)
		goto out;

	if (adm_ctx.resource) {
		if (info->nlhdr->nlmsg_flags & NLM_F_EXCL) {
			retcode = ERR_INVALID_REQUEST;
			drbd_msg_put_info(adm_ctx.reply_skb, "resource exists");
		}
		/* else: still NO_ERROR */
		goto out;
	}

	/* not yet safe for genl_family.parallel_ops */
	mutex_lock(&resources_mutex);
	connection = conn_create(adm_ctx.resource_name, &res_opts);
	mutex_unlock(&resources_mutex);

	if (connection) {
		struct resource_info resource_info;

		mutex_lock(&notification_mutex);
		resource_to_info(&resource_info, connection->resource);
		notify_resource_state(NULL, 0, connection->resource,
				      &resource_info, NOTIFY_CREATE);
		mutex_unlock(&notification_mutex);
	} else
		retcode = ERR_NOMEM;

out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}