#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ block_size; } ;
struct se_device {TYPE_2__ dev_attrib; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
struct fd_dev {unsigned long long fd_dev_size; struct file* fd_file; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 struct fd_dev* FD_DEV (struct se_device*) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (scalar_t__,scalar_t__) ; 
 unsigned long long i_size_read (struct inode*) ; 

__attribute__((used)) static sector_t fd_get_blocks(struct se_device *dev)
{
	struct fd_dev *fd_dev = FD_DEV(dev);
	struct file *f = fd_dev->fd_file;
	struct inode *i = f->f_mapping->host;
	unsigned long long dev_size;
	/*
	 * When using a file that references an underlying struct block_device,
	 * ensure dev_size is always based on the current inode size in order
	 * to handle underlying block_device resize operations.
	 */
	if (S_ISBLK(i->i_mode))
		dev_size = i_size_read(i);
	else
		dev_size = fd_dev->fd_dev_size;

	return div_u64(dev_size - dev->dev_attrib.block_size,
		       dev->dev_attrib.block_size);
}