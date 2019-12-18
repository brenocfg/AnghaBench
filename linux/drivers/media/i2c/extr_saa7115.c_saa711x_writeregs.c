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
struct saa711x_state {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 scalar_t__ saa711x_has_reg (int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ saa711x_write (struct v4l2_subdev*,unsigned char,unsigned char) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned char) ; 

__attribute__((used)) static int saa711x_writeregs(struct v4l2_subdev *sd, const unsigned char *regs)
{
	struct saa711x_state *state = to_state(sd);
	unsigned char reg, data;

	while (*regs != 0x00) {
		reg = *(regs++);
		data = *(regs++);

		/* According with datasheets, reserved regs should be
		   filled with 0 - seems better not to touch on they */
		if (saa711x_has_reg(state->ident, reg)) {
			if (saa711x_write(sd, reg, data) < 0)
				return -1;
		} else {
			v4l2_dbg(1, debug, sd, "tried to access reserved reg 0x%02x\n", reg);
		}
	}
	return 0;
}