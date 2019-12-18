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
struct seq_file {int /*<<< orphan*/  poll_event; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_event_count ; 
 int /*<<< orphan*/  md_seq_ops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int md_seq_open(struct inode *inode, struct file *file)
{
	struct seq_file *seq;
	int error;

	error = seq_open(file, &md_seq_ops);
	if (error)
		return error;

	seq = file->private_data;
	seq->poll_event = atomic_read(&md_event_count);
	return error;
}