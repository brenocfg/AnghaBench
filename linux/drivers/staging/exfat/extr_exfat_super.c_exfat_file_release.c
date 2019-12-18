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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ fid; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_I (struct inode*) ; 
 int /*<<< orphan*/  ffsSyncVol (struct super_block*,int) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 

__attribute__((used)) static int exfat_file_release(struct inode *inode, struct file *filp)
{
	struct super_block *sb = inode->i_sb;

	EXFAT_I(inode)->fid.size = i_size_read(inode);
	ffsSyncVol(sb, false);
	return 0;
}