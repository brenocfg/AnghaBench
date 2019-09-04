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
struct s6e8aa0 {int error; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 struct s6e8aa0* panel_to_s6e8aa0 (struct drm_panel*) ; 
 int s6e8aa0_power_on (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_set_sequence (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_unprepare (struct drm_panel*) ; 

__attribute__((used)) static int s6e8aa0_prepare(struct drm_panel *panel)
{
	struct s6e8aa0 *ctx = panel_to_s6e8aa0(panel);
	int ret;

	ret = s6e8aa0_power_on(ctx);
	if (ret < 0)
		return ret;

	s6e8aa0_set_sequence(ctx);
	ret = ctx->error;

	if (ret < 0)
		s6e8aa0_unprepare(panel);

	return ret;
}