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
struct efx_ef10_filter_table {unsigned int rx_match_count; int /*<<< orphan*/ * rx_match_mcdi_flags; } ;
typedef  enum efx_filter_match_flags { ____Placeholder_efx_filter_match_flags } efx_filter_match_flags ;

/* Variables and functions */
 int efx_ef10_filter_match_flags_from_mcdi (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool efx_ef10_filter_match_supported(struct efx_ef10_filter_table *table,
					    bool encap,
					    enum efx_filter_match_flags match_flags)
{
	unsigned int match_pri;
	int mf;

	for (match_pri = 0;
	     match_pri < table->rx_match_count;
	     match_pri++) {
		mf = efx_ef10_filter_match_flags_from_mcdi(encap,
				table->rx_match_mcdi_flags[match_pri]);
		if (mf == match_flags)
			return true;
	}

	return false;
}