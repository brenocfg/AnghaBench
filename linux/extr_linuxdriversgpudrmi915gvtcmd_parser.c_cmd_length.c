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
struct parser_exec_state {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_val (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 int get_cmd_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cmd_length(struct parser_exec_state *s)
{
	return get_cmd_length(s->info, cmd_val(s, 0));
}