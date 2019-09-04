#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cx24120_state {TYPE_1__* config; } ;
struct cx24120_initial_mpeg_config {int x1; int x2; int x3; } ;
struct cx24120_cmd {int len; int* arg; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {struct cx24120_initial_mpeg_config initial_mpeg_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MPEG_INIT ; 
 int cx24120_message_send (struct cx24120_state*,struct cx24120_cmd*) ; 

__attribute__((used)) static int cx24120_msg_mpeg_output_config(struct cx24120_state *state, u8 seq)
{
	struct cx24120_cmd cmd;
	struct cx24120_initial_mpeg_config i =
			state->config->initial_mpeg_config;

	cmd.id = CMD_MPEG_INIT;
	cmd.len = 7;
	cmd.arg[0] = seq; /* sequental number - can be 0,1,2 */
	cmd.arg[1] = ((i.x1 & 0x01) << 1) | ((i.x1 >> 1) & 0x01);
	cmd.arg[2] = 0x05;
	cmd.arg[3] = 0x02;
	cmd.arg[4] = ((i.x2 >> 1) & 0x01);
	cmd.arg[5] = (i.x2 & 0xf0) | (i.x3 & 0x0f);
	cmd.arg[6] = 0x10;

	return cx24120_message_send(state, &cmd);
}