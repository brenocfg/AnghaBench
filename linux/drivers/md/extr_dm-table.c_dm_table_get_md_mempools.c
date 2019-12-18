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
struct dm_table {struct dm_md_mempools* mempools; } ;
struct dm_md_mempools {int dummy; } ;

/* Variables and functions */

struct dm_md_mempools *dm_table_get_md_mempools(struct dm_table *t)
{
	return t->mempools;
}