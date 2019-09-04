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
struct pvrdma_id_table {int /*<<< orphan*/  table; } ;
struct TYPE_2__ {struct pvrdma_id_table tbl; } ;
struct pvrdma_dev {TYPE_1__ uar_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void pvrdma_uar_table_cleanup(struct pvrdma_dev *dev)
{
	struct pvrdma_id_table *tbl = &dev->uar_table.tbl;

	kfree(tbl->table);
}