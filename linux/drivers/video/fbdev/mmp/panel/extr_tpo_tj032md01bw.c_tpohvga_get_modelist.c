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
struct mmp_panel {int dummy; } ;
struct mmp_mode {int dummy; } ;

/* Variables and functions */
 struct mmp_mode* mmp_modes_tpohvga ; 

__attribute__((used)) static int tpohvga_get_modelist(struct mmp_panel *panel,
		struct mmp_mode **modelist)
{
	*modelist = mmp_modes_tpohvga;
	return 1;
}