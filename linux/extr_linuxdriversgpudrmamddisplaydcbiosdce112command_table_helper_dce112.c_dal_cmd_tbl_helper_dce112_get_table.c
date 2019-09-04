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
struct command_table_helper {int dummy; } ;

/* Variables and functions */
 struct command_table_helper const command_table_helper_funcs ; 

const struct command_table_helper *dal_cmd_tbl_helper_dce112_get_table(void)
{
	return &command_table_helper_funcs;
}