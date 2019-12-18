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
struct mcde_dsi {int /*<<< orphan*/  dev; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct mcde_dsi* bridge_to_mcde_dsi (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mcde_dsi_bridge_enable(struct drm_bridge *bridge)
{
	struct mcde_dsi *d = bridge_to_mcde_dsi(bridge);

	dev_info(d->dev, "enable DSI master\n");
}