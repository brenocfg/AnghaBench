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
struct se_lun {int lun_tg_pt_secondary_write_md; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

ssize_t core_alua_show_secondary_write_metadata(
	struct se_lun *lun,
	char *page)
{
	return sprintf(page, "%d\n", lun->lun_tg_pt_secondary_write_md);
}