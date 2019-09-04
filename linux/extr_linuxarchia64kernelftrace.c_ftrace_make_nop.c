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
struct module {int dummy; } ;
struct dyn_ftrace {int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int ftrace_make_nop_check (struct dyn_ftrace*,unsigned long) ; 
 int ftrace_modify_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* ftrace_nop_replace () ; 

int ftrace_make_nop(struct module *mod,
		    struct dyn_ftrace *rec, unsigned long addr)
{
	int ret;
	char *new;

	ret = ftrace_make_nop_check(rec, addr);
	if (ret)
		return ret;
	new = ftrace_nop_replace();
	return ftrace_modify_code(rec->ip, NULL, new, 0);
}