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
struct super_block {int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct inode {int /*<<< orphan*/  i_fop; int /*<<< orphan*/ * i_op; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IBMASMFS_MAGIC ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  ibmasmfs_create_files (struct super_block*) ; 
 int /*<<< orphan*/  ibmasmfs_dir_ops ; 
 struct inode* ibmasmfs_make_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  ibmasmfs_s_ops ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 

__attribute__((used)) static int ibmasmfs_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct inode *root;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = IBMASMFS_MAGIC;
	sb->s_op = &ibmasmfs_s_ops;
	sb->s_time_gran = 1;

	root = ibmasmfs_make_inode (sb, S_IFDIR | 0500);
	if (!root)
		return -ENOMEM;

	root->i_op = &simple_dir_inode_operations;
	root->i_fop = ibmasmfs_dir_ops;

	sb->s_root = d_make_root(root);
	if (!sb->s_root)
		return -ENOMEM;

	ibmasmfs_create_files(sb);
	return 0;
}