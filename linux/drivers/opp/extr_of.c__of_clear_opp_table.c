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
struct opp_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _opp_table_free_required_tables (struct opp_table*) ; 

void _of_clear_opp_table(struct opp_table *opp_table)
{
	_opp_table_free_required_tables(opp_table);
}