#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_bdev; } ;
struct bd_info_t {int opened; int sector_size_bits; int num_sectors; scalar_t__ sector_size; scalar_t__ sector_size_mask; } ;
struct TYPE_4__ {struct bd_info_t bd_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ bdev_logical_block_size (TYPE_1__*) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int ilog2 (scalar_t__) ; 

void bdev_open(struct super_block *sb)
{
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	if (p_bd->opened)
		return;

	p_bd->sector_size      = bdev_logical_block_size(sb->s_bdev);
	p_bd->sector_size_bits = ilog2(p_bd->sector_size);
	p_bd->sector_size_mask = p_bd->sector_size - 1;
	p_bd->num_sectors      = i_size_read(sb->s_bdev->bd_inode) >>
				 p_bd->sector_size_bits;
	p_bd->opened = true;
}