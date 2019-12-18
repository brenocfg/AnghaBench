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
struct gb_lights_set_fade_request {int /*<<< orphan*/  fade_out; int /*<<< orphan*/  fade_in; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  light_id; } ;
struct gb_connection {struct gb_bundle* bundle; } ;
struct gb_channel {int /*<<< orphan*/  fade_out; int /*<<< orphan*/  fade_in; int /*<<< orphan*/  id; TYPE_1__* light; scalar_t__ releasing; } ;
struct gb_bundle {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GB_LIGHTS_TYPE_SET_FADE ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_lights_set_fade_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 struct gb_connection* get_conn_from_channel (struct gb_channel*) ; 

__attribute__((used)) static int gb_lights_fade_set(struct gb_channel *channel)
{
	struct gb_connection *connection = get_conn_from_channel(channel);
	struct gb_bundle *bundle = connection->bundle;
	struct gb_lights_set_fade_request req;
	int ret;

	if (channel->releasing)
		return -ESHUTDOWN;

	ret = gb_pm_runtime_get_sync(bundle);
	if (ret < 0)
		return ret;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.fade_in = channel->fade_in;
	req.fade_out = channel->fade_out;
	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_FADE,
				&req, sizeof(req), NULL, 0);

	gb_pm_runtime_put_autosuspend(bundle);

	return ret;
}