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
struct TYPE_2__ {int /*<<< orphan*/  total_entries; } ;
struct gasket_page_table {int /*<<< orphan*/  mutex; int /*<<< orphan*/  extended_offset_reg; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  gasket_page_table_unmap_all_nolock (struct gasket_page_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gasket_page_table_reset(struct gasket_page_table *pg_tbl)
{
	mutex_lock(&pg_tbl->mutex);
	gasket_page_table_unmap_all_nolock(pg_tbl);
	writeq(pg_tbl->config.total_entries, pg_tbl->extended_offset_reg);
	mutex_unlock(&pg_tbl->mutex);
}