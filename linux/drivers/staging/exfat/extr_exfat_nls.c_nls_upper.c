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
typedef  int /*<<< orphan*/  u16 ;
struct super_block {int dummy; } ;
struct fs_info_t {int /*<<< orphan*/ ** vol_utbl; } ;
struct TYPE_3__ {scalar_t__ casesensitive; } ;
struct TYPE_4__ {TYPE_1__ options; struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 size_t get_col_index (int /*<<< orphan*/ ) ; 
 size_t get_row_index (int /*<<< orphan*/ ) ; 

u16 nls_upper(struct super_block *sb, u16 a)
{
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if (EXFAT_SB(sb)->options.casesensitive)
		return a;
	if (p_fs->vol_utbl && p_fs->vol_utbl[get_col_index(a)])
		return p_fs->vol_utbl[get_col_index(a)][get_row_index(a)];
	else
		return a;
}