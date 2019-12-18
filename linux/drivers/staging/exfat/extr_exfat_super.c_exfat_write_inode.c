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
struct writeback_control {int dummy; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct dir_entry_t {int /*<<< orphan*/  AccessTimestamp; int /*<<< orphan*/  CreateTimestamp; int /*<<< orphan*/  ModifyTimestamp; int /*<<< orphan*/  Size; int /*<<< orphan*/  Attr; } ;

/* Variables and functions */
 scalar_t__ EXFAT_ROOT_INO ; 
 int /*<<< orphan*/  exfat_make_attr (struct inode*) ; 
 int /*<<< orphan*/  exfat_time_unix2fat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffsWriteStat (struct inode*,struct dir_entry_t*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 

__attribute__((used)) static int exfat_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct dir_entry_t info;

	if (inode->i_ino == EXFAT_ROOT_INO)
		return 0;

	info.Attr = exfat_make_attr(inode);
	info.Size = i_size_read(inode);

	exfat_time_unix2fat(&inode->i_mtime, &info.ModifyTimestamp);
	exfat_time_unix2fat(&inode->i_ctime, &info.CreateTimestamp);
	exfat_time_unix2fat(&inode->i_atime, &info.AccessTimestamp);

	ffsWriteStat(inode, &info);

	return 0;
}