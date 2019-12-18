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
struct seq_tab {size_t rows; void* data; size_t width; scalar_t__ skip_first; } ;
typedef  size_t loff_t ;

/* Variables and functions */

__attribute__((used)) static void *seq_tab_get_idx(struct seq_tab *tb, loff_t pos)
{
	pos -= tb->skip_first;
	return pos >= tb->rows ? NULL : &tb->data[pos * tb->width];
}