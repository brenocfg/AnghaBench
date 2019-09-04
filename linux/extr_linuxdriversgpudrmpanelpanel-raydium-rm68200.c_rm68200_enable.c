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
struct rm68200 {int enabled; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 struct rm68200* panel_to_rm68200 (struct drm_panel*) ; 

__attribute__((used)) static int rm68200_enable(struct drm_panel *panel)
{
	struct rm68200 *ctx = panel_to_rm68200(panel);

	if (ctx->enabled)
		return 0;

	backlight_enable(ctx->backlight);

	ctx->enabled = true;

	return 0;
}