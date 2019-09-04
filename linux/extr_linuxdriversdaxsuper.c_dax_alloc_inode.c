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
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_rdev; } ;
struct dax_device {struct inode inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dax_cache ; 
 struct dax_device* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *dax_alloc_inode(struct super_block *sb)
{
	struct dax_device *dax_dev;
	struct inode *inode;

	dax_dev = kmem_cache_alloc(dax_cache, GFP_KERNEL);
	if (!dax_dev)
		return NULL;

	inode = &dax_dev->inode;
	inode->i_rdev = 0;
	return inode;
}