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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {struct v4l2_subdev sd; } ;

/* Variables and functions */
 int CLK_CFG_DIS ; 
 int CLK_CFG_SEL_ACLK ; 
 int CLK_CFG_SEL_ACLK_EN ; 
 int PON_DIS ; 
 int PON_EN ; 
 int /*<<< orphan*/  REG_CLK_CFG ; 
 int /*<<< orphan*/  REG_MODE_REC_CFG1 ; 
 int /*<<< orphan*/  REG_PON_CBIAS ; 
 int /*<<< orphan*/  REG_PON_OVR_EN ; 
 int /*<<< orphan*/  REG_PON_PLL ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tda1997x_reset_n1(struct tda1997x_state *state)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 reg;

	/* clear HDMI mode flag in BCAPS */
	io_write(sd, REG_CLK_CFG, CLK_CFG_SEL_ACLK_EN | CLK_CFG_SEL_ACLK);
	io_write(sd, REG_PON_OVR_EN, PON_EN);
	io_write(sd, REG_PON_CBIAS, PON_EN);
	io_write(sd, REG_PON_PLL, PON_EN);

	reg = io_read(sd, REG_MODE_REC_CFG1);
	reg &= ~0x06;
	reg |= 0x02;
	io_write(sd, REG_MODE_REC_CFG1, reg);
	io_write(sd, REG_CLK_CFG, CLK_CFG_DIS);
	io_write(sd, REG_PON_OVR_EN, PON_DIS);
	reg = io_read(sd, REG_MODE_REC_CFG1);
	reg &= ~0x06;
	io_write(sd, REG_MODE_REC_CFG1, reg);
}