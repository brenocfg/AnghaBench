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
struct rain {char* cmd; int /*<<< orphan*/  adap; } ;
struct cec_msg {scalar_t__ len; scalar_t__ msg; } ;

/* Variables and functions */
 scalar_t__ CEC_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  CEC_TX_STATUS_LOW_DRIVE ; 
 int /*<<< orphan*/  CEC_TX_STATUS_NACK ; 
 int /*<<< orphan*/  CEC_TX_STATUS_OK ; 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,struct cec_msg*) ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hex2bin (scalar_t__,char const*,int) ; 
 int hex_to_bin (char const) ; 
 scalar_t__ isxdigit (char const) ; 

__attribute__((used)) static void rain_process_msg(struct rain *rain)
{
	struct cec_msg msg = {};
	const char *cmd = rain->cmd + 3;
	int stat = -1;

	for (; *cmd; cmd++) {
		if (!isxdigit(*cmd))
			continue;
		if (isxdigit(cmd[0]) && isxdigit(cmd[1])) {
			if (msg.len == CEC_MAX_MSG_SIZE)
				break;
			if (hex2bin(msg.msg + msg.len, cmd, 1))
				continue;
			msg.len++;
			cmd++;
			continue;
		}
		if (!cmd[1])
			stat = hex_to_bin(cmd[0]);
		break;
	}

	if (rain->cmd[0] == 'R') {
		if (stat == 1 || stat == 2)
			cec_received_msg(rain->adap, &msg);
		return;
	}

	switch (stat) {
	case 1:
		cec_transmit_attempt_done(rain->adap, CEC_TX_STATUS_OK);
		break;
	case 2:
		cec_transmit_attempt_done(rain->adap, CEC_TX_STATUS_NACK);
		break;
	default:
		cec_transmit_attempt_done(rain->adap, CEC_TX_STATUS_LOW_DRIVE);
		break;
	}
}