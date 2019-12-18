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
struct v4l2_subdev {int dummy; } ;
struct gs {int enabled; int /*<<< orphan*/  pdev; int /*<<< orphan*/  current_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_FORCE_FMT ; 
 int get_register_timings (int /*<<< orphan*/ *) ; 
 int gs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct gs* to_gs (struct v4l2_subdev*) ; 

__attribute__((used)) static int gs_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct gs *gs = to_gs(sd);
	int reg_value;

	if (gs->enabled == enable)
		return 0;

	gs->enabled = enable;

	if (enable) {
		/* To force the specific format */
		reg_value = get_register_timings(&gs->current_timings);
		return gs_write_register(gs->pdev, REG_FORCE_FMT, reg_value);
	}

	/* To renable auto-detection mode */
	return gs_write_register(gs->pdev, REG_FORCE_FMT, 0x0);
}