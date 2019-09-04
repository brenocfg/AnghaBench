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
struct dm_thin_new_mapping {TYPE_1__* tc; int /*<<< orphan*/  list; int /*<<< orphan*/  cell; } ;
struct TYPE_4__ {int /*<<< orphan*/  mapping_pool; } ;
struct TYPE_3__ {TYPE_2__* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  cell_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct dm_thin_new_mapping*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_prepared_mapping_fail(struct dm_thin_new_mapping *m)
{
	cell_error(m->tc->pool, m->cell);
	list_del(&m->list);
	mempool_free(m, &m->tc->pool->mapping_pool);
}