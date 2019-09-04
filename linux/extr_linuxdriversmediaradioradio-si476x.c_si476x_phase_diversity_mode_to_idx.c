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
 int SI476X_IDX_PHDIV_DISABLED ; 
 int SI476X_IDX_PHDIV_PRIMARY_ANTENNA ; 
 int SI476X_IDX_PHDIV_PRIMARY_COMBINING ; 
 int SI476X_IDX_PHDIV_SECONDARY_ANTENNA ; 
 int SI476X_IDX_PHDIV_SECONDARY_COMBINING ; 
#define  SI476X_PHDIV_DISABLED 132 
#define  SI476X_PHDIV_PRIMARY_ANTENNA 131 
#define  SI476X_PHDIV_PRIMARY_COMBINING 130 
#define  SI476X_PHDIV_SECONDARY_ANTENNA 129 
#define  SI476X_PHDIV_SECONDARY_COMBINING 128 

__attribute__((used)) static inline enum phase_diversity_modes_idx
si476x_phase_diversity_mode_to_idx(enum si476x_phase_diversity_mode mode)
{
	switch (mode) {
	default:		/* FALLTHROUGH */
	case SI476X_PHDIV_DISABLED:
		return SI476X_IDX_PHDIV_DISABLED;
	case SI476X_PHDIV_PRIMARY_COMBINING:
		return SI476X_IDX_PHDIV_PRIMARY_COMBINING;
	case SI476X_PHDIV_PRIMARY_ANTENNA:
		return SI476X_IDX_PHDIV_PRIMARY_ANTENNA;
	case SI476X_PHDIV_SECONDARY_ANTENNA:
		return SI476X_IDX_PHDIV_SECONDARY_ANTENNA;
	case SI476X_PHDIV_SECONDARY_COMBINING:
		return SI476X_IDX_PHDIV_SECONDARY_COMBINING;
	}
}