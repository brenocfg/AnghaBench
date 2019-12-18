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
struct super_block {int /*<<< orphan*/  s_bdi; TYPE_1__* s_mtd; int /*<<< orphan*/  s_dev; } ;
struct fs_context {TYPE_1__* sget_key; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_BLOCK_MAJOR ; 
 int /*<<< orphan*/  bdi_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_bdi ; 

__attribute__((used)) static int mtd_set_super(struct super_block *sb, struct fs_context *fc)
{
	sb->s_mtd = fc->sget_key;
	sb->s_dev = MKDEV(MTD_BLOCK_MAJOR, sb->s_mtd->index);
	sb->s_bdi = bdi_get(mtd_bdi);
	return 0;
}