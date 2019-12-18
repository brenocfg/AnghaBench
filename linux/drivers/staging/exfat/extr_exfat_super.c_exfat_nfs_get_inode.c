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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_generation; } ;

/* Variables and functions */
 scalar_t__ EXFAT_ROOT_INO ; 
 struct inode* ilookup (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct inode *exfat_nfs_get_inode(struct super_block *sb, u64 ino,
					 u32 generation)
{
	struct inode *inode = NULL;

	if (ino < EXFAT_ROOT_INO)
		return inode;
	inode = ilookup(sb, ino);

	if (inode && generation && (inode->i_generation != generation)) {
		iput(inode);
		inode = NULL;
	}

	return inode;
}