#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  file; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {scalar_t__ last_scan_results_count; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 TYPE_1__* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *prism2_scan_results_proc_next(struct seq_file *m, void *v, loff_t *_pos)
{
	local_info_t *local = PDE_DATA(file_inode(m->file));

	++*_pos;
	if (*_pos > local->last_scan_results_count)
		return NULL;
	return (void *)(unsigned long)(*_pos + 1); /* 0 would be EOF */
}