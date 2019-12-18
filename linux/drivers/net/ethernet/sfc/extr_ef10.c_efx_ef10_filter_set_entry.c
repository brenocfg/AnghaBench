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
struct efx_filter_spec {int dummy; } ;
struct efx_ef10_filter_table {TYPE_1__* entry; } ;
struct TYPE_2__ {unsigned long spec; } ;

/* Variables and functions */

__attribute__((used)) static void
efx_ef10_filter_set_entry(struct efx_ef10_filter_table *table,
			  unsigned int filter_idx,
			  const struct efx_filter_spec *spec,
			  unsigned int flags)
{
	table->entry[filter_idx].spec =	(unsigned long)spec | flags;
}