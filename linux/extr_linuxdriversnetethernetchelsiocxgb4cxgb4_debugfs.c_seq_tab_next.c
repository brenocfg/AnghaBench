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
struct seq_file {int /*<<< orphan*/  private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* seq_tab_get_idx (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void *seq_tab_next(struct seq_file *seq, void *v, loff_t *pos)
{
	v = seq_tab_get_idx(seq->private, *pos + 1);
	if (v)
		++*pos;
	return v;
}