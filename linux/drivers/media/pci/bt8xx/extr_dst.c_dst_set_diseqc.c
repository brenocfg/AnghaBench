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
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; int /*<<< orphan*/  msg; } ;
struct dst_state {scalar_t__ dst_type; int dst_hw_cap; } ;

/* Variables and functions */
 int DST_TYPE_HAS_DISEQC5 ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int dst_check_sum (int*,int) ; 
 int dst_command (struct dst_state*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dst_set_diseqc(struct dvb_frontend *fe, struct dvb_diseqc_master_cmd *cmd)
{
	struct dst_state *state = fe->demodulator_priv;
	u8 packet[8] = { 0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf0, 0xec };

	if (state->dst_type != DST_TYPE_IS_SAT)
		return -EOPNOTSUPP;
	if (cmd->msg_len > 0 && cmd->msg_len < 5)
		memcpy(&packet[3], cmd->msg, cmd->msg_len);
	else if (cmd->msg_len == 5 && state->dst_hw_cap & DST_TYPE_HAS_DISEQC5)
		memcpy(&packet[2], cmd->msg, cmd->msg_len);
	else
		return -EINVAL;
	packet[7] = dst_check_sum(&packet[0], 7);
	return dst_command(state, packet, 8);
}