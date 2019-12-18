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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ prism2_download_aux_dump_npages ; 

__attribute__((used)) static void *prism2_download_aux_dump_proc_next(struct seq_file *m, void *v, loff_t *_pos)
{
	++*_pos;
	if (*_pos >= prism2_download_aux_dump_npages)
		return NULL;
	return (void *)((unsigned long)*_pos + 1);
}