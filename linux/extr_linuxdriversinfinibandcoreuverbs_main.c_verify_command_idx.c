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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* uverbs_cmd_table ; 
 scalar_t__* uverbs_ex_cmd_table ; 

__attribute__((used)) static bool verify_command_idx(u32 command, bool extended)
{
	if (extended)
		return command < ARRAY_SIZE(uverbs_ex_cmd_table) &&
		       uverbs_ex_cmd_table[command];

	return command < ARRAY_SIZE(uverbs_cmd_table) &&
	       uverbs_cmd_table[command];
}