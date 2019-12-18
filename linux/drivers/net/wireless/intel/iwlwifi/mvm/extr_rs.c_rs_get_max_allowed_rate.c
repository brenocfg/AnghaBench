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
struct rs_tx_column {int mode; } ;
struct iwl_lq_sta {int max_legacy_rate_idx; int max_siso_rate_idx; int max_mimo2_rate_idx; } ;

/* Variables and functions */
#define  RS_LEGACY 130 
#define  RS_MIMO2 129 
#define  RS_SISO 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static int rs_get_max_allowed_rate(struct iwl_lq_sta *lq_sta,
				   const struct rs_tx_column *column)
{
	switch (column->mode) {
	case RS_LEGACY:
		return lq_sta->max_legacy_rate_idx;
	case RS_SISO:
		return lq_sta->max_siso_rate_idx;
	case RS_MIMO2:
		return lq_sta->max_mimo2_rate_idx;
	default:
		WARN_ON_ONCE(1);
	}

	return lq_sta->max_legacy_rate_idx;
}