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

/* Variables and functions */
 int ANDROID_WIFI_CMD_MAX ; 
 int /*<<< orphan*/ * android_wifi_cmd_str ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_android_cmdstr_to_num(char *cmdstr)
{
	int cmd_num;

	for (cmd_num = 0; cmd_num < ANDROID_WIFI_CMD_MAX; cmd_num++)
		if (!strncasecmp(cmdstr, android_wifi_cmd_str[cmd_num],
				  strlen(android_wifi_cmd_str[cmd_num])))
			break;
	return cmd_num;
}