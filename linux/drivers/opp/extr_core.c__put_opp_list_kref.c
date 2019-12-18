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
struct opp_table {int /*<<< orphan*/  list_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  _opp_table_list_kref_release ; 
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_table_lock ; 

void _put_opp_list_kref(struct opp_table *opp_table)
{
	kref_put_mutex(&opp_table->list_kref, _opp_table_list_kref_release,
		       &opp_table_lock);
}