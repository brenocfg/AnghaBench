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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int __FAT_read (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int FAT_read(struct super_block *sb, u32 loc, u32 *content)
{
	s32 ret;

	down(&f_sem);
	ret = __FAT_read(sb, loc, content);
	up(&f_sem);

	return ret;
}