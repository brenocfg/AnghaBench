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
typedef  int umode_t ;
struct inode {int i_mode; } ;
struct TYPE_2__ {int fs_fmask; int fs_dmask; } ;
struct exfat_sb_info {TYPE_1__ options; } ;
typedef  int mode_t ;

/* Variables and functions */
 int EPERM ; 
 int S_IFMT ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ exfat_mode_can_hold_ro (struct inode*) ; 

__attribute__((used)) static int exfat_sanitize_mode(const struct exfat_sb_info *sbi,
			       struct inode *inode, umode_t *mode_ptr)
{
	mode_t i_mode, mask, perm;

	i_mode = inode->i_mode;

	if (S_ISREG(i_mode) || S_ISLNK(i_mode))
		mask = sbi->options.fs_fmask;
	else
		mask = sbi->options.fs_dmask;

	perm = *mode_ptr & ~(S_IFMT | mask);

	/* Of the r and x bits, all (subject to umask) must be present.*/
	if ((perm & 0555) != (i_mode & 0555))
		return -EPERM;

	if (exfat_mode_can_hold_ro(inode)) {
		/*
		 * Of the w bits, either all (subject to umask) or none must be
		 * present.
		 */
		if ((perm & 0222) && ((perm & 0222) != (0222 & ~mask)))
			return -EPERM;
	} else {
		/*
		 * If exfat_mode_can_hold_ro(inode) is false, can't change w
		 * bits.
		 */
		if ((perm & 0222) != (0222 & ~mask))
			return -EPERM;
	}

	*mode_ptr &= S_IFMT | perm;

	return 0;
}