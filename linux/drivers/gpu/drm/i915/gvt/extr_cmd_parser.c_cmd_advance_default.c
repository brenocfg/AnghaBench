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
 int /*<<< orphan*/  cmd_length (struct parser_exec_state*) ; 
 int ip_gma_advance (struct parser_exec_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_advance_default(struct parser_exec_state *s)
{
	return ip_gma_advance(s, cmd_length(s));
}