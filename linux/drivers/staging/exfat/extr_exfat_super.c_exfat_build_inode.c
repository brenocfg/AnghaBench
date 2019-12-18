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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct file_id_t {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXFAT_ROOT_INO ; 
 int /*<<< orphan*/  SET_IVERSION (struct inode*,int) ; 
 int /*<<< orphan*/  exfat_attach (struct inode*,int /*<<< orphan*/ ) ; 
 int exfat_fill_inode (struct inode*,struct file_id_t*) ; 
 struct inode* exfat_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  iunique (struct super_block*,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 

__attribute__((used)) static struct inode *exfat_build_inode(struct super_block *sb,
				       struct file_id_t *fid, loff_t i_pos)
{
	struct inode *inode;
	int err;

	inode = exfat_iget(sb, i_pos);
	if (inode)
		goto out;
	inode = new_inode(sb);
	if (!inode) {
		inode = ERR_PTR(-ENOMEM);
		goto out;
	}
	inode->i_ino = iunique(sb, EXFAT_ROOT_INO);
	SET_IVERSION(inode, 1);
	err = exfat_fill_inode(inode, fid);
	if (err) {
		iput(inode);
		inode = ERR_PTR(err);
		goto out;
	}
	exfat_attach(inode, i_pos);
	insert_inode_hash(inode);
out:
	return inode;
}