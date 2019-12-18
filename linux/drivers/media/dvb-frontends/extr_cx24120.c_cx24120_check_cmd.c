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
struct cx24120_state {int dummy; } ;

/* Variables and functions */
#define  CMD_CLOCK_READ 134 
#define  CMD_DISEQC_BURST 133 
#define  CMD_DISEQC_MSG1 132 
#define  CMD_DISEQC_MSG2 131 
#define  CMD_SETTONE 130 
#define  CMD_SETVOLTAGE 129 
#define  CMD_TUNEREQUEST 128 
 int /*<<< orphan*/  cx24120_msg_mpeg_output_global_config (struct cx24120_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx24120_check_cmd(struct cx24120_state *state, u8 id)
{
	switch (id) {
	case CMD_TUNEREQUEST:
	case CMD_CLOCK_READ:
	case CMD_DISEQC_MSG1:
	case CMD_DISEQC_MSG2:
	case CMD_SETVOLTAGE:
	case CMD_SETTONE:
	case CMD_DISEQC_BURST:
		cx24120_msg_mpeg_output_global_config(state, 0);
		/* Old driver would do a msleep(100) here */
	default:
		return;
	}
}