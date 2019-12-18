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
typedef  int /*<<< orphan*/  u8 ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __buf_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_sem ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

u8 *buf_getblk(struct super_block *sb, sector_t sec)
{
	u8 *buf;

	down(&b_sem);
	buf = __buf_getblk(sb, sec);
	up(&b_sem);

	return buf;
}