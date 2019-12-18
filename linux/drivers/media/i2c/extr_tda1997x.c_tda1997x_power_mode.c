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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {struct v4l2_subdev sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_VP_ENABLE ; 
 int /*<<< orphan*/  PON_DIS ; 
 int /*<<< orphan*/  PON_EN ; 
 int /*<<< orphan*/  REG_CFG1 ; 
 int /*<<< orphan*/  REG_DEEP_PLL7_BYP ; 
 int /*<<< orphan*/  REG_OF ; 
 int /*<<< orphan*/  REG_PON_OVR_EN ; 
 int /*<<< orphan*/  io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tda1997x_power_mode(struct tda1997x_state *state, bool enable)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 reg;

	if (enable) {
		/* Automatic control of TMDS */
		io_write(sd, REG_PON_OVR_EN, PON_DIS);
		/* Enable current bias unit */
		io_write(sd, REG_CFG1, PON_EN);
		/* Enable deep color PLL */
		io_write(sd, REG_DEEP_PLL7_BYP, PON_DIS);
		/* Output buffers active */
		reg = io_read(sd, REG_OF);
		reg &= ~OF_VP_ENABLE;
		io_write(sd, REG_OF, reg);
	} else {
		/* Power down EDID mode sequence */
		/* Output buffers in HiZ */
		reg = io_read(sd, REG_OF);
		reg |= OF_VP_ENABLE;
		io_write(sd, REG_OF, reg);
		/* Disable deep color PLL */
		io_write(sd, REG_DEEP_PLL7_BYP, PON_EN);
		/* Disable current bias unit */
		io_write(sd, REG_CFG1, PON_DIS);
		/* Manual control of TMDS */
		io_write(sd, REG_PON_OVR_EN, PON_EN);
	}
}