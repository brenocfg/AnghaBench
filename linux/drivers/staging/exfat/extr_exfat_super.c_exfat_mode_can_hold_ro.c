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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int fs_fmask; } ;
struct exfat_sb_info {TYPE_1__ options; } ;

/* Variables and functions */
 struct exfat_sb_info* EXFAT_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int exfat_mode_can_hold_ro(struct inode *inode)
{
	struct exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);

	if (S_ISDIR(inode->i_mode))
		return 0;

	if ((~sbi->options.fs_fmask) & 0222)
		return 1;
	return 0;
}