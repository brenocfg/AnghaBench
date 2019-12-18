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
struct parser_exec_state {int dummy; } ;
struct mi_display_flip_command_info {int dummy; } ;

/* Variables and functions */
 int gen8_check_mi_display_flip (struct parser_exec_state*,struct mi_display_flip_command_info*) ; 

__attribute__((used)) static int check_mi_display_flip(struct parser_exec_state *s,
		struct mi_display_flip_command_info *info)
{
	return gen8_check_mi_display_flip(s, info);
}