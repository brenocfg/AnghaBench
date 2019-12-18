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
typedef  scalar_t__ u8 ;
struct gb_lights_set_brightness_request {scalar_t__ brightness; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  light_id; } ;
struct gb_connection {struct gb_bundle* bundle; } ;
struct gb_channel {int active; int /*<<< orphan*/  lock; TYPE_2__* led; int /*<<< orphan*/  id; TYPE_1__* light; } ;
struct gb_bundle {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_4__ {scalar_t__ brightness; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_LIGHTS_TYPE_SET_BRIGHTNESS ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_lights_set_brightness_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 struct gb_connection* get_conn_from_channel (struct gb_channel*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __gb_lights_led_brightness_set(struct gb_channel *channel)
{
	struct gb_lights_set_brightness_request req;
	struct gb_connection *connection = get_conn_from_channel(channel);
	struct gb_bundle *bundle = connection->bundle;
	bool old_active;
	int ret;

	mutex_lock(&channel->lock);
	ret = gb_pm_runtime_get_sync(bundle);
	if (ret < 0)
		goto out_unlock;

	old_active = channel->active;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.brightness = (u8)channel->led->brightness;

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_BRIGHTNESS,
				&req, sizeof(req), NULL, 0);
	if (ret < 0)
		goto out_pm_put;

	if (channel->led->brightness)
		channel->active = true;
	else
		channel->active = false;

	/* we need to keep module alive when turning to active state */
	if (!old_active && channel->active)
		goto out_unlock;

	/*
	 * on the other hand if going to inactive we still hold a reference and
	 * need to put it, so we could go to suspend.
	 */
	if (old_active && !channel->active)
		gb_pm_runtime_put_autosuspend(bundle);

out_pm_put:
	gb_pm_runtime_put_autosuspend(bundle);
out_unlock:
	mutex_unlock(&channel->lock);

	return ret;
}