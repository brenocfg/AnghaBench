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
struct otm8009a {int enabled; int /*<<< orphan*/  bl_dev; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 struct otm8009a* panel_to_otm8009a (struct drm_panel*) ; 

__attribute__((used)) static int otm8009a_enable(struct drm_panel *panel)
{
	struct otm8009a *ctx = panel_to_otm8009a(panel);

	if (ctx->enabled)
		return 0;

	backlight_enable(ctx->bl_dev);

	ctx->enabled = true;

	return 0;
}