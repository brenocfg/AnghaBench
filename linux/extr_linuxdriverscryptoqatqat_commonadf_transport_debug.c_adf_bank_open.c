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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_bank_sops ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adf_bank_open(struct inode *inode, struct file *file)
{
	int ret = seq_open(file, &adf_bank_sops);

	if (!ret) {
		struct seq_file *seq_f = file->private_data;

		seq_f->private = inode->i_private;
	}
	return ret;
}