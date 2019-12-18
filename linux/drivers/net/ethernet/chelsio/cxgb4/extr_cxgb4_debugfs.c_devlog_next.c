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
struct seq_file {struct devlog_info* private; } ;
struct devlog_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* devlog_get_idx (struct devlog_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *devlog_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct devlog_info *dinfo = seq->private;

	(*pos)++;
	return devlog_get_idx(dinfo, *pos);
}