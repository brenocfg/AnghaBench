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
struct pool {struct dm_thin_new_mapping* next_mapping; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/ * bio; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dm_thin_new_mapping*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dm_thin_new_mapping *get_next_mapping(struct pool *pool)
{
	struct dm_thin_new_mapping *m = pool->next_mapping;

	BUG_ON(!pool->next_mapping);

	memset(m, 0, sizeof(struct dm_thin_new_mapping));
	INIT_LIST_HEAD(&m->list);
	m->bio = NULL;

	pool->next_mapping = NULL;

	return m;
}