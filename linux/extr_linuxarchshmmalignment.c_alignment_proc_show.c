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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  se_dword ; 
 int /*<<< orphan*/  se_half ; 
 int se_kernmode_warn ; 
 int /*<<< orphan*/  se_multi ; 
 int /*<<< orphan*/  se_sys ; 
 int /*<<< orphan*/  se_user ; 
 size_t se_usermode ; 
 char** se_usermode_action ; 
 int /*<<< orphan*/  se_word ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static int alignment_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "User:\t\t%lu\n", se_user);
	seq_printf(m, "System:\t\t%lu\n", se_sys);
	seq_printf(m, "Half:\t\t%lu\n", se_half);
	seq_printf(m, "Word:\t\t%lu\n", se_word);
	seq_printf(m, "DWord:\t\t%lu\n", se_dword);
	seq_printf(m, "Multi:\t\t%lu\n", se_multi);
	seq_printf(m, "User faults:\t%i (%s)\n", se_usermode,
			se_usermode_action[se_usermode]);
	seq_printf(m, "Kernel faults:\t%i (fixup%s)\n", se_kernmode_warn,
			se_kernmode_warn ? "+warn" : "");
	return 0;
}