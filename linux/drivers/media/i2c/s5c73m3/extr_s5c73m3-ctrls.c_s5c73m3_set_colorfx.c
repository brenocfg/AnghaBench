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
struct TYPE_4__ {TYPE_1__* colorfx; } ;
struct s5c73m3 {TYPE_2__ ctrls; int /*<<< orphan*/  sensor_sd; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short const**) ; 
 int /*<<< orphan*/  COMM_IMAGE_EFFECT ; 
#define  COMM_IMAGE_EFFECT_AQUA 137 
#define  COMM_IMAGE_EFFECT_MONO 136 
#define  COMM_IMAGE_EFFECT_NEGATIVE 135 
#define  COMM_IMAGE_EFFECT_NONE 134 
#define  COMM_IMAGE_EFFECT_SEPIA 133 
 int EINVAL ; 
#define  V4L2_COLORFX_AQUA 132 
#define  V4L2_COLORFX_BW 131 
#define  V4L2_COLORFX_NEGATIVE 130 
#define  V4L2_COLORFX_NONE 129 
#define  V4L2_COLORFX_SEPIA 128 
 int /*<<< orphan*/  s5c73m3_dbg ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,unsigned short const) ; 
 int /*<<< orphan*/ * v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5c73m3_set_colorfx(struct s5c73m3 *state, int val)
{
	static const unsigned short colorfx[][2] = {
		{ V4L2_COLORFX_NONE,	 COMM_IMAGE_EFFECT_NONE },
		{ V4L2_COLORFX_BW,	 COMM_IMAGE_EFFECT_MONO },
		{ V4L2_COLORFX_SEPIA,	 COMM_IMAGE_EFFECT_SEPIA },
		{ V4L2_COLORFX_NEGATIVE, COMM_IMAGE_EFFECT_NEGATIVE },
		{ V4L2_COLORFX_AQUA,	 COMM_IMAGE_EFFECT_AQUA },
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(colorfx); i++) {
		if (colorfx[i][0] != val)
			continue;

		v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
			 "Setting %s color effect\n",
			 v4l2_ctrl_get_menu(state->ctrls.colorfx->id)[i]);

		return s5c73m3_isp_command(state, COMM_IMAGE_EFFECT,
					 colorfx[i][1]);
	}
	return -EINVAL;
}