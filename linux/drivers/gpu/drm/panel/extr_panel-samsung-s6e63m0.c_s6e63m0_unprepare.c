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
struct s6e63m0 {int prepared; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 struct s6e63m0* panel_to_s6e63m0 (struct drm_panel*) ; 
 int /*<<< orphan*/  s6e63m0_clear_error (struct s6e63m0*) ; 
 int s6e63m0_power_off (struct s6e63m0*) ; 

__attribute__((used)) static int s6e63m0_unprepare(struct drm_panel *panel)
{
	struct s6e63m0 *ctx = panel_to_s6e63m0(panel);
	int ret;

	if (!ctx->prepared)
		return 0;

	s6e63m0_clear_error(ctx);

	ret = s6e63m0_power_off(ctx);
	if (ret < 0)
		return ret;

	ctx->prepared = false;

	return 0;
}