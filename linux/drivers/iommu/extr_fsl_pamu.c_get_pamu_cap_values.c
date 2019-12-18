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

/* Variables and functions */
 scalar_t__ PAMU_PC3 ; 
 int PAMU_PC3_MWCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ *) ; 
 int max_subwindow_count ; 

__attribute__((used)) static void get_pamu_cap_values(unsigned long pamu_reg_base)
{
	u32 pc_val;

	pc_val = in_be32((u32 *)(pamu_reg_base + PAMU_PC3));
	/* Maximum number of subwindows per liodn */
	max_subwindow_count = 1 << (1 + PAMU_PC3_MWCE(pc_val));
}