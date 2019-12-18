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
 int /*<<< orphan*/  CMD_GET_MIB ; 
 int /*<<< orphan*/  CMD_JOIN ; 
 int /*<<< orphan*/  CMD_RADIO_OFF ; 
 int /*<<< orphan*/  CMD_RADIO_ON ; 
 int /*<<< orphan*/  CMD_SCAN ; 
 int /*<<< orphan*/  CMD_SET_MIB ; 
 int /*<<< orphan*/  CMD_STARTUP ; 
 int /*<<< orphan*/  CMD_START_IBSS ; 
 int /*<<< orphan*/  MAKE_CMD_CASE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *at76_get_cmd_string(u8 cmd_status)
{
	switch (cmd_status) {
		MAKE_CMD_CASE(CMD_SET_MIB);
		MAKE_CMD_CASE(CMD_GET_MIB);
		MAKE_CMD_CASE(CMD_SCAN);
		MAKE_CMD_CASE(CMD_JOIN);
		MAKE_CMD_CASE(CMD_START_IBSS);
		MAKE_CMD_CASE(CMD_RADIO_ON);
		MAKE_CMD_CASE(CMD_RADIO_OFF);
		MAKE_CMD_CASE(CMD_STARTUP);
	}

	return "UNKNOWN";
}