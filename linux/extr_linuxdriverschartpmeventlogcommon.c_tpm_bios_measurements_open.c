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
struct tpm_chip_seqops {struct tpm_chip* chip; struct seq_operations* seqops; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct seq_operations {int dummy; } ;
struct seq_file {struct tpm_chip* private; } ;
struct inode {scalar_t__ i_private; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int seq_open (struct file*,struct seq_operations const*) ; 

__attribute__((used)) static int tpm_bios_measurements_open(struct inode *inode,
					    struct file *file)
{
	int err;
	struct seq_file *seq;
	struct tpm_chip_seqops *chip_seqops;
	const struct seq_operations *seqops;
	struct tpm_chip *chip;

	inode_lock(inode);
	if (!inode->i_private) {
		inode_unlock(inode);
		return -ENODEV;
	}
	chip_seqops = (struct tpm_chip_seqops *)inode->i_private;
	seqops = chip_seqops->seqops;
	chip = chip_seqops->chip;
	get_device(&chip->dev);
	inode_unlock(inode);

	/* now register seq file */
	err = seq_open(file, seqops);
	if (!err) {
		seq = file->private_data;
		seq->private = chip;
	}

	return err;
}