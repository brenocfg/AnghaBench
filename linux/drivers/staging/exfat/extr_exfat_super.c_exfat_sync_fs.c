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

/* Variables and functions */
 scalar_t__ __is_sb_dirty (struct super_block*) ; 
 int /*<<< orphan*/  __lock_super (struct super_block*) ; 
 int /*<<< orphan*/  __set_sb_clean (struct super_block*) ; 
 int /*<<< orphan*/  __unlock_super (struct super_block*) ; 
 int ffsSyncVol (struct super_block*,int) ; 

__attribute__((used)) static int exfat_sync_fs(struct super_block *sb, int wait)
{
	int err = 0;

	if (__is_sb_dirty(sb)) {
		__lock_super(sb);
		__set_sb_clean(sb);
		err = ffsSyncVol(sb, true);
		__unlock_super(sb);
	}

	return err;
}