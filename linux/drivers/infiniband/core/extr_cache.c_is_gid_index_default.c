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
struct ib_gid_table {int default_gid_indices; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 

__attribute__((used)) static bool is_gid_index_default(const struct ib_gid_table *table,
				 unsigned int index)
{
	return index < 32 && (BIT(index) & table->default_gid_indices);
}