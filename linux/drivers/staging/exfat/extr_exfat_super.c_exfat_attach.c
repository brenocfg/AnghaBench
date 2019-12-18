#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hlist_head {int dummy; } ;
struct exfat_sb_info {int /*<<< orphan*/  inode_hash_lock; struct hlist_head* inode_hashtable; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_hash_fat; int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_I (struct inode*) ; 
 struct exfat_sb_info* EXFAT_SB (int /*<<< orphan*/ ) ; 
 int exfat_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exfat_attach(struct inode *inode, loff_t i_pos)
{
	struct exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);
	struct hlist_head *head = sbi->inode_hashtable + exfat_hash(i_pos);

	spin_lock(&sbi->inode_hash_lock);
	EXFAT_I(inode)->i_pos = i_pos;
	hlist_add_head(&EXFAT_I(inode)->i_hash_fat, head);
	spin_unlock(&sbi->inode_hash_lock);
}