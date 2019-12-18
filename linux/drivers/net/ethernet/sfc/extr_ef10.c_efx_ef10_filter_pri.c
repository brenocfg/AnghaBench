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
typedef  scalar_t__ u32 ;
struct efx_filter_spec {int dummy; } ;
struct efx_ef10_filter_table {unsigned int rx_match_count; scalar_t__* rx_match_mcdi_flags; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 scalar_t__ efx_ef10_filter_mcdi_flags_from_spec (struct efx_filter_spec const*) ; 

__attribute__((used)) static int efx_ef10_filter_pri(struct efx_ef10_filter_table *table,
			       const struct efx_filter_spec *spec)
{
	u32 mcdi_flags = efx_ef10_filter_mcdi_flags_from_spec(spec);
	unsigned int match_pri;

	for (match_pri = 0;
	     match_pri < table->rx_match_count;
	     match_pri++)
		if (table->rx_match_mcdi_flags[match_pri] == mcdi_flags)
			return match_pri;

	return -EPROTONOSUPPORT;
}