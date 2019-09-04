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
struct spufs_inode_info {struct spu_context* i_ctx; } ;
struct spu_context {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct spu_context* private_data; } ;

/* Variables and functions */
 struct spufs_inode_info* SPUFS_I (struct inode*) ; 

__attribute__((used)) static int spufs_info_open(struct inode *inode, struct file *file)
{
	struct spufs_inode_info *i = SPUFS_I(inode);
	struct spu_context *ctx = i->i_ctx;
	file->private_data = ctx;
	return 0;
}