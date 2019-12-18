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
struct vic {int /*<<< orphan*/  dev; } ;
struct tegra_drm_context {int /*<<< orphan*/  channel; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_channel_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct vic* to_vic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vic_close_channel(struct tegra_drm_context *context)
{
	struct vic *vic = to_vic(context->client);

	host1x_channel_put(context->channel);

	pm_runtime_put(vic->dev);
}