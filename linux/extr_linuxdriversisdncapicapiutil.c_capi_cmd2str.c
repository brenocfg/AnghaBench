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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 size_t command_2_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** mnames ; 

char *capi_cmd2str(u8 cmd, u8 subcmd)
{
	char *result;

	result = mnames[command_2_index(cmd, subcmd)];
	if (result == NULL)
		result = "INVALID_COMMAND";
	return result;
}