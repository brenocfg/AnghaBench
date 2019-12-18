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
typedef  int u64 ;
typedef  int u32 ;
struct cx24120_state {TYPE_2__* i2c; TYPE_1__* config; } ;
struct cx24120_cmd {int len; int* arg; int /*<<< orphan*/  id; } ;
typedef  int inv_vco ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int xtal_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_VCO_SET ; 
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 

__attribute__((used)) static int cx24120_set_vco(struct cx24120_state *state)
{
	struct cx24120_cmd cmd;
	u32 nxtal_khz, vco;
	u64 inv_vco;
	u32 xtal_khz = state->config->xtal_khz;

	nxtal_khz = xtal_khz * 4;
	vco = nxtal_khz * 10;
	inv_vco = DIV_ROUND_CLOSEST_ULL(0x400000000ULL, vco);

	dev_dbg(&state->i2c->dev, "xtal=%d, vco=%d, inv_vco=%lld\n",
		xtal_khz, vco, inv_vco);

	cmd.id = CMD_VCO_SET;
	cmd.len = 12;
	cmd.arg[0] = (vco >> 16) & 0xff;
	cmd.arg[1] = (vco >> 8) & 0xff;
	cmd.arg[2] = vco & 0xff;
	cmd.arg[3] = (inv_vco >> 8) & 0xff;
	cmd.arg[4] = (inv_vco) & 0xff;
	cmd.arg[5] = 0x03;
	cmd.arg[6] = (nxtal_khz >> 8) & 0xff;
	cmd.arg[7] = nxtal_khz & 0xff;
	cmd.arg[8] = 0x06;
	cmd.arg[9] = 0x03;
	cmd.arg[10] = (xtal_khz >> 16) & 0xff;
	cmd.arg[11] = xtal_khz & 0xff;

	return cx24120_message_send(state, &cmd);
}