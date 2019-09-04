#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* scene_mode; } ;
struct s5c73m3 {TYPE_2__ ctrls; int /*<<< orphan*/  sensor_sd; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_SCENE_MODE ; 
#define  COMM_SCENE_MODE_AGAINST_LIGHT 141 
#define  COMM_SCENE_MODE_BEACH 140 
#define  COMM_SCENE_MODE_CANDLE 139 
#define  COMM_SCENE_MODE_DAWN 138 
#define  COMM_SCENE_MODE_FALL 137 
#define  COMM_SCENE_MODE_FIRE 136 
#define  COMM_SCENE_MODE_INDOOR 135 
#define  COMM_SCENE_MODE_LANDSCAPE 134 
#define  COMM_SCENE_MODE_NIGHT 133 
#define  COMM_SCENE_MODE_NONE 132 
#define  COMM_SCENE_MODE_PORTRAIT 131 
#define  COMM_SCENE_MODE_SPORTS 130 
#define  COMM_SCENE_MODE_SUNSET 129 
#define  COMM_SCENE_MODE_TEXT 128 
 int /*<<< orphan*/  s5c73m3_dbg ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,unsigned short const) ; 
 int /*<<< orphan*/ * v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5c73m3_set_scene_program(struct s5c73m3 *state, int val)
{
	static const unsigned short scene_lookup[] = {
		COMM_SCENE_MODE_NONE,	     /* V4L2_SCENE_MODE_NONE */
		COMM_SCENE_MODE_AGAINST_LIGHT,/* V4L2_SCENE_MODE_BACKLIGHT */
		COMM_SCENE_MODE_BEACH,	     /* V4L2_SCENE_MODE_BEACH_SNOW */
		COMM_SCENE_MODE_CANDLE,	     /* V4L2_SCENE_MODE_CANDLE_LIGHT */
		COMM_SCENE_MODE_DAWN,	     /* V4L2_SCENE_MODE_DAWN_DUSK */
		COMM_SCENE_MODE_FALL,	     /* V4L2_SCENE_MODE_FALL_COLORS */
		COMM_SCENE_MODE_FIRE,	     /* V4L2_SCENE_MODE_FIREWORKS */
		COMM_SCENE_MODE_LANDSCAPE,    /* V4L2_SCENE_MODE_LANDSCAPE */
		COMM_SCENE_MODE_NIGHT,	     /* V4L2_SCENE_MODE_NIGHT */
		COMM_SCENE_MODE_INDOOR,	     /* V4L2_SCENE_MODE_PARTY_INDOOR */
		COMM_SCENE_MODE_PORTRAIT,     /* V4L2_SCENE_MODE_PORTRAIT */
		COMM_SCENE_MODE_SPORTS,	     /* V4L2_SCENE_MODE_SPORTS */
		COMM_SCENE_MODE_SUNSET,	     /* V4L2_SCENE_MODE_SUNSET */
		COMM_SCENE_MODE_TEXT,	     /* V4L2_SCENE_MODE_TEXT */
	};

	v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd, "Setting %s scene mode\n",
		 v4l2_ctrl_get_menu(state->ctrls.scene_mode->id)[val]);

	return s5c73m3_isp_command(state, COMM_SCENE_MODE, scene_lookup[val]);
}