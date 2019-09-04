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
struct kernfs_open_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_cmd_status ; 
 int /*<<< orphan*/  last_cmd_status_buf ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int seq_buf_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int rdt_last_cmd_status_show(struct kernfs_open_file *of,
				    struct seq_file *seq, void *v)
{
	int len;

	mutex_lock(&rdtgroup_mutex);
	len = seq_buf_used(&last_cmd_status);
	if (len)
		seq_printf(seq, "%.*s", len, last_cmd_status_buf);
	else
		seq_puts(seq, "ok\n");
	mutex_unlock(&rdtgroup_mutex);
	return 0;
}