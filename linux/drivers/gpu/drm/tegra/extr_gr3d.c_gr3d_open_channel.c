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
struct tegra_drm_context {int /*<<< orphan*/  channel; } ;
struct tegra_drm_client {int dummy; } ;
struct gr3d {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  host1x_channel_get (int /*<<< orphan*/ ) ; 
 struct gr3d* to_gr3d (struct tegra_drm_client*) ; 

__attribute__((used)) static int gr3d_open_channel(struct tegra_drm_client *client,
			     struct tegra_drm_context *context)
{
	struct gr3d *gr3d = to_gr3d(client);

	context->channel = host1x_channel_get(gr3d->channel);
	if (!context->channel)
		return -ENOMEM;

	return 0;
}