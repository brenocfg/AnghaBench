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
struct rockchip_rgb {int /*<<< orphan*/  encoder; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_bridge_remove (int /*<<< orphan*/ ) ; 

void rockchip_rgb_fini(struct rockchip_rgb *rgb)
{
	drm_panel_bridge_remove(rgb->bridge);
	drm_encoder_cleanup(&rgb->encoder);
}