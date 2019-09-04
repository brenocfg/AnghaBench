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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_table1 ; 
 int /*<<< orphan*/  init_table2 ; 
 int /*<<< orphan*/  init_table3 ; 
 int /*<<< orphan*/  setup_hazard_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table1 ; 
 int /*<<< orphan*/  table2 ; 
 int /*<<< orphan*/  table3 ; 

void via_init_command_verifier(void)
{
	setup_hazard_table(init_table1, table1, ARRAY_SIZE(init_table1));
	setup_hazard_table(init_table2, table2, ARRAY_SIZE(init_table2));
	setup_hazard_table(init_table3, table3, ARRAY_SIZE(init_table3));
}