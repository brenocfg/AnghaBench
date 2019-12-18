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
struct super_block {int dummy; } ;
struct bd_info_t {int opened; } ;
struct TYPE_2__ {struct bd_info_t bd_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 

void bdev_close(struct super_block *sb)
{
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	p_bd->opened = false;
}