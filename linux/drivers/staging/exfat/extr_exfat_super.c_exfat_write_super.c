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
 int /*<<< orphan*/  __lock_super (struct super_block*) ; 
 int /*<<< orphan*/  __set_sb_clean (struct super_block*) ; 
 int /*<<< orphan*/  __unlock_super (struct super_block*) ; 
 int /*<<< orphan*/  ffsSyncVol (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

__attribute__((used)) static void exfat_write_super(struct super_block *sb)
{
	__lock_super(sb);

	__set_sb_clean(sb);

	if (!sb_rdonly(sb))
		ffsSyncVol(sb, true);

	__unlock_super(sb);
}