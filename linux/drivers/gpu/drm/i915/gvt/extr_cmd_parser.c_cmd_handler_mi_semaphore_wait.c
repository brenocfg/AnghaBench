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

/* Variables and functions */
 int unexpected_cmd (struct parser_exec_state*) ; 

__attribute__((used)) static int cmd_handler_mi_semaphore_wait(struct parser_exec_state *s)
{
	return unexpected_cmd(s);
}