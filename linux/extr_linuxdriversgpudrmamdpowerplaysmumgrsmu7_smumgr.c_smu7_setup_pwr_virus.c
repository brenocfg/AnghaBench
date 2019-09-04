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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_pwr_dfy_table (struct pp_hwmgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  execute_pwr_table (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwr_virus_section1 ; 
 int /*<<< orphan*/  pwr_virus_section2 ; 
 int /*<<< orphan*/  pwr_virus_section3 ; 
 int /*<<< orphan*/  pwr_virus_section4 ; 
 int /*<<< orphan*/  pwr_virus_section5 ; 
 int /*<<< orphan*/  pwr_virus_section6 ; 
 int /*<<< orphan*/  pwr_virus_table_post ; 
 int /*<<< orphan*/  pwr_virus_table_pre ; 

int smu7_setup_pwr_virus(struct pp_hwmgr *hwmgr)
{
	execute_pwr_table(hwmgr, pwr_virus_table_pre, ARRAY_SIZE(pwr_virus_table_pre));
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section1);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section2);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section3);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section4);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section5);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section6);
	execute_pwr_table(hwmgr, pwr_virus_table_post, ARRAY_SIZE(pwr_virus_table_post));

	return 0;
}