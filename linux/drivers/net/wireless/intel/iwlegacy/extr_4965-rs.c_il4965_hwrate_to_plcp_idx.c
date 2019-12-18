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
typedef  int u32 ;
struct TYPE_3__ {int plcp; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IL_FIRST_OFDM_RATE ; 
 int IL_LAST_OFDM_RATE ; 
 int RATE_9M_IDX ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MIMO2_6M_PLCP ; 
 TYPE_1__* il_rates ; 

__attribute__((used)) static int
il4965_hwrate_to_plcp_idx(u32 rate_n_flags)
{
	int idx = 0;

	/* HT rate format */
	if (rate_n_flags & RATE_MCS_HT_MSK) {
		idx = (rate_n_flags & 0xff);

		if (idx >= RATE_MIMO2_6M_PLCP)
			idx = idx - RATE_MIMO2_6M_PLCP;

		idx += IL_FIRST_OFDM_RATE;
		/* skip 9M not supported in ht */
		if (idx >= RATE_9M_IDX)
			idx += 1;
		if (idx >= IL_FIRST_OFDM_RATE && idx <= IL_LAST_OFDM_RATE)
			return idx;

		/* legacy rate format, search for match in table */
	} else {
		for (idx = 0; idx < ARRAY_SIZE(il_rates); idx++)
			if (il_rates[idx].plcp == (rate_n_flags & 0xFF))
				return idx;
	}

	return -1;
}