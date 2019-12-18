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
struct inode {struct adapter* i_private; } ;
struct file {struct seq_file* private_data; } ;
struct adapter {int /*<<< orphan*/  l2t; } ;

/* Variables and functions */
 int /*<<< orphan*/  l2t_seq_ops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2t_seq_open(struct inode *inode, struct file *file)
{
	int rc = seq_open(file, &l2t_seq_ops);

	if (!rc) {
		struct adapter *adap = inode->i_private;
		struct seq_file *seq = file->private_data;

		seq->private = adap->l2t;
	}
	return rc;
}