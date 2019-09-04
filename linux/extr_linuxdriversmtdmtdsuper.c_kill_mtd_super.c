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
struct super_block {int /*<<< orphan*/ * s_mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_shutdown_super (struct super_block*) ; 
 int /*<<< orphan*/  put_mtd_device (int /*<<< orphan*/ *) ; 

void kill_mtd_super(struct super_block *sb)
{
	generic_shutdown_super(sb);
	put_mtd_device(sb->s_mtd);
	sb->s_mtd = NULL;
}