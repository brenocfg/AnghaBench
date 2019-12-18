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
struct saa711x_state {int enable; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa711x_has_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int saa711x_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct saa711x_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s output\n",
			enable ? "enable" : "disable");

	if (state->enable == enable)
		return 0;
	state->enable = enable;
	if (!saa711x_has_reg(state->ident, R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED))
		return 0;
	saa711x_write(sd, R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, state->enable);
	return 0;
}