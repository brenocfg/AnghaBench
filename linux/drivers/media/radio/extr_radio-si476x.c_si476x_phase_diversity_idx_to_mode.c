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
typedef  enum si476x_phase_diversity_mode { ____Placeholder_si476x_phase_diversity_mode } si476x_phase_diversity_mode ;
typedef  enum phase_diversity_modes_idx { ____Placeholder_phase_diversity_modes_idx } phase_diversity_modes_idx ;

/* Variables and functions */
#define  SI476X_IDX_PHDIV_DISABLED 137 
#define  SI476X_IDX_PHDIV_PRIMARY_ANTENNA 136 
#define  SI476X_IDX_PHDIV_PRIMARY_COMBINING 135 
#define  SI476X_IDX_PHDIV_SECONDARY_ANTENNA 134 
#define  SI476X_IDX_PHDIV_SECONDARY_COMBINING 133 
#define  SI476X_PHDIV_DISABLED 132 
#define  SI476X_PHDIV_PRIMARY_ANTENNA 131 
#define  SI476X_PHDIV_PRIMARY_COMBINING 130 
#define  SI476X_PHDIV_SECONDARY_ANTENNA 129 
#define  SI476X_PHDIV_SECONDARY_COMBINING 128 

__attribute__((used)) static inline enum si476x_phase_diversity_mode
si476x_phase_diversity_idx_to_mode(enum phase_diversity_modes_idx idx)
{
	static const int idx_to_value[] = {
		[SI476X_IDX_PHDIV_DISABLED]		= SI476X_PHDIV_DISABLED,
		[SI476X_IDX_PHDIV_PRIMARY_COMBINING]	= SI476X_PHDIV_PRIMARY_COMBINING,
		[SI476X_IDX_PHDIV_PRIMARY_ANTENNA]	= SI476X_PHDIV_PRIMARY_ANTENNA,
		[SI476X_IDX_PHDIV_SECONDARY_ANTENNA]	= SI476X_PHDIV_SECONDARY_ANTENNA,
		[SI476X_IDX_PHDIV_SECONDARY_COMBINING]	= SI476X_PHDIV_SECONDARY_COMBINING,
	};

	return idx_to_value[idx];
}