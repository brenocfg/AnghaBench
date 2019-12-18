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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct exfat_sb_info {int dummy; } ;

/* Variables and functions */
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 scalar_t__ __is_sb_dirty (struct super_block*) ; 
 int /*<<< orphan*/  exfat_free_super (struct exfat_sb_info*) ; 
 int /*<<< orphan*/  exfat_write_super (struct super_block*) ; 
 int /*<<< orphan*/  ffsUmountVol (struct super_block*) ; 

__attribute__((used)) static void exfat_put_super(struct super_block *sb)
{
	struct exfat_sb_info *sbi = EXFAT_SB(sb);

	if (__is_sb_dirty(sb))
		exfat_write_super(sb);

	ffsUmountVol(sb);

	sb->s_fs_info = NULL;
	exfat_free_super(sbi);
}