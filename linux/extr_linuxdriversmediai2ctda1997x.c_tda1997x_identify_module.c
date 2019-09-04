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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_state {int tmdsb_clk; int tmdsb_soc; int port_30bit; int output_2p5; void* chip_revision; TYPE_2__* client; TYPE_1__* info; struct v4l2_subdev sd; } ;
typedef  enum tda1997x_type { ____Placeholder_tda1997x_type } tda1997x_type ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  REG_CMTP_REG10 ; 
 int /*<<< orphan*/  REG_CMTP_REG11 ; 
 int TDA19971 ; 
 int TDA19973 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda1997x_identify_module(struct tda1997x_state *state)
{
	struct v4l2_subdev *sd = &state->sd;
	enum tda1997x_type type;
	u8 reg;

	/* Read chip configuration*/
	reg = io_read(sd, REG_CMTP_REG10);
	state->tmdsb_clk = (reg >> 6) & 0x01; /* use tmds clock B_inv for B */
	state->tmdsb_soc = (reg >> 5) & 0x01; /* tmds of input B */
	state->port_30bit = (reg >> 2) & 0x03; /* 30bit vs 24bit */
	state->output_2p5 = (reg >> 1) & 0x01; /* output supply 2.5v */
	switch ((reg >> 4) & 0x03) {
	case 0x00:
		type = TDA19971;
		break;
	case 0x02:
	case 0x03:
		type = TDA19973;
		break;
	default:
		dev_err(&state->client->dev, "unsupported chip ID\n");
		return -EIO;
	}
	if (state->info->type != type) {
		dev_err(&state->client->dev, "chip id mismatch\n");
		return -EIO;
	}

	/* read chip revision */
	state->chip_revision = io_read(sd, REG_CMTP_REG11);

	return 0;
}