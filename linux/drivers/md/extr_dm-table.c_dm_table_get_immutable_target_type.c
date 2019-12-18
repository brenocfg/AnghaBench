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
struct target_type {int dummy; } ;
struct dm_table {struct target_type* immutable_target_type; } ;

/* Variables and functions */

struct target_type *dm_table_get_immutable_target_type(struct dm_table *t)
{
	return t->immutable_target_type;
}