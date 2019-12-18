#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ plcp; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IWL_FIRST_HT_RATE ; 
 int IWL_FIRST_VHT_RATE ; 
 int IWL_LAST_HE_RATE ; 
 int IWL_LAST_HT_RATE ; 
 int IWL_LAST_VHT_RATE ; 
 int IWL_RATE_9M_INDEX ; 
 int IWL_RATE_INVALID ; 
 scalar_t__ IWL_RATE_MCS_0_INDEX ; 
 int RATE_HT_MCS_RATE_CODE_MSK ; 
 int RATE_MCS_HE_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_VHT_MSK ; 
 int RATE_VHT_MCS_RATE_CODE_MSK ; 
 TYPE_1__* iwl_rates ; 
 scalar_t__ rs_extract_rate (int) ; 

__attribute__((used)) static int iwl_hwrate_to_plcp_idx(u32 rate_n_flags)
{
	int idx = 0;

	if (rate_n_flags & RATE_MCS_HT_MSK) {
		idx = rate_n_flags & RATE_HT_MCS_RATE_CODE_MSK;
		idx += IWL_RATE_MCS_0_INDEX;

		/* skip 9M not supported in HT*/
		if (idx >= IWL_RATE_9M_INDEX)
			idx += 1;
		if ((idx >= IWL_FIRST_HT_RATE) && (idx <= IWL_LAST_HT_RATE))
			return idx;
	} else if (rate_n_flags & RATE_MCS_VHT_MSK ||
		   rate_n_flags & RATE_MCS_HE_MSK) {
		idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		idx += IWL_RATE_MCS_0_INDEX;

		/* skip 9M not supported in VHT*/
		if (idx >= IWL_RATE_9M_INDEX)
			idx++;
		if ((idx >= IWL_FIRST_VHT_RATE) && (idx <= IWL_LAST_VHT_RATE))
			return idx;
		if ((rate_n_flags & RATE_MCS_HE_MSK) &&
		    (idx <= IWL_LAST_HE_RATE))
			return idx;
	} else {
		/* legacy rate format, search for match in table */

		u8 legacy_rate = rs_extract_rate(rate_n_flags);
		for (idx = 0; idx < ARRAY_SIZE(iwl_rates); idx++)
			if (iwl_rates[idx].plcp == legacy_rate)
				return idx;
	}

	return IWL_RATE_INVALID;
}