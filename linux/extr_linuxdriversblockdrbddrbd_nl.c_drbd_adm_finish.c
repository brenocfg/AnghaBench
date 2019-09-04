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
struct genl_info {int dummy; } ;
struct drbd_config_context {int /*<<< orphan*/  reply_skb; TYPE_3__* reply_dh; TYPE_2__* resource; TYPE_1__* connection; TYPE_4__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  kref; } ;
struct TYPE_7__ {int ret_code; } ;
struct TYPE_6__ {int /*<<< orphan*/  kref; } ;
struct TYPE_5__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  drbd_adm_send_reply (int /*<<< orphan*/ ,struct genl_info*) ; 
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int /*<<< orphan*/ * drbd_destroy_device ; 
 int /*<<< orphan*/ * drbd_destroy_resource ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbd_adm_finish(struct drbd_config_context *adm_ctx,
	struct genl_info *info, int retcode)
{
	if (adm_ctx->device) {
		kref_put(&adm_ctx->device->kref, drbd_destroy_device);
		adm_ctx->device = NULL;
	}
	if (adm_ctx->connection) {
		kref_put(&adm_ctx->connection->kref, &drbd_destroy_connection);
		adm_ctx->connection = NULL;
	}
	if (adm_ctx->resource) {
		kref_put(&adm_ctx->resource->kref, drbd_destroy_resource);
		adm_ctx->resource = NULL;
	}

	if (!adm_ctx->reply_skb)
		return -ENOMEM;

	adm_ctx->reply_dh->ret_code = retcode;
	drbd_adm_send_reply(adm_ctx->reply_skb, info);
	return 0;
}