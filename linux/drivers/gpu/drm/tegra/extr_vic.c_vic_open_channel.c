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
struct vic {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel; } ;
struct tegra_drm_context {int /*<<< orphan*/  channel; } ;
struct tegra_drm_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  host1x_channel_get (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct vic* to_vic (struct tegra_drm_client*) ; 
 int vic_boot (struct vic*) ; 
 int vic_load_firmware (struct vic*) ; 

__attribute__((used)) static int vic_open_channel(struct tegra_drm_client *client,
			    struct tegra_drm_context *context)
{
	struct vic *vic = to_vic(client);
	int err;

	err = pm_runtime_get_sync(vic->dev);
	if (err < 0)
		return err;

	err = vic_load_firmware(vic);
	if (err < 0)
		goto rpm_put;

	err = vic_boot(vic);
	if (err < 0)
		goto rpm_put;

	context->channel = host1x_channel_get(vic->channel);
	if (!context->channel) {
		err = -ENOMEM;
		goto rpm_put;
	}

	return 0;

rpm_put:
	pm_runtime_put(vic->dev);
	return err;
}