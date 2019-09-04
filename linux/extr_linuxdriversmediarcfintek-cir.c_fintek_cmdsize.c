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

/* Variables and functions */
 int BUF_CMD_G_REVISION ; 
#define  BUF_CMD_SIG_END 136 
#define  BUF_CMD_S_CARRIER 135 
#define  BUF_CMD_S_RXSENSOR 134 
#define  BUF_CMD_S_TIMEOUT 133 
#define  BUF_CMD_S_TXMASK 132 
#define  BUF_COMMAND_HEADER 131 
#define  BUF_COMMAND_NULL 130 
#define  BUF_HW_CMD_HEADER 129 
#define  BUF_RSP_PULSE_COUNT 128 

__attribute__((used)) static int fintek_cmdsize(u8 cmd, u8 subcmd)
{
	int datasize = 0;

	switch (cmd) {
	case BUF_COMMAND_NULL:
		if (subcmd == BUF_HW_CMD_HEADER)
			datasize = 1;
		break;
	case BUF_HW_CMD_HEADER:
		if (subcmd == BUF_CMD_G_REVISION)
			datasize = 2;
		break;
	case BUF_COMMAND_HEADER:
		switch (subcmd) {
		case BUF_CMD_S_CARRIER:
		case BUF_CMD_S_TIMEOUT:
		case BUF_RSP_PULSE_COUNT:
			datasize = 2;
			break;
		case BUF_CMD_SIG_END:
		case BUF_CMD_S_TXMASK:
		case BUF_CMD_S_RXSENSOR:
			datasize = 1;
			break;
		}
	}

	return datasize;
}