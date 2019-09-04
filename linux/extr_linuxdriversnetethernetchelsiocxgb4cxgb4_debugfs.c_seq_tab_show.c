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
struct seq_tab {int (* show ) (struct seq_file*,void*,int) ;char* data; int width; } ;
struct seq_file {struct seq_tab* private; } ;

/* Variables and functions */
 int stub1 (struct seq_file*,void*,int) ; 

__attribute__((used)) static int seq_tab_show(struct seq_file *seq, void *v)
{
	const struct seq_tab *tb = seq->private;

	return tb->show(seq, v, ((char *)v - tb->data) / tb->width);
}