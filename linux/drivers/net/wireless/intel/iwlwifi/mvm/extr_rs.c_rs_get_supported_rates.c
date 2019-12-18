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
typedef  int /*<<< orphan*/  u16 ;
struct rs_rate {int dummy; } ;
struct iwl_lq_sta {int /*<<< orphan*/  active_mimo2_rate; int /*<<< orphan*/  active_siso_rate; int /*<<< orphan*/  active_legacy_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ is_legacy (struct rs_rate*) ; 
 scalar_t__ is_mimo2 (struct rs_rate*) ; 
 scalar_t__ is_siso (struct rs_rate*) ; 

__attribute__((used)) static u16 rs_get_supported_rates(struct iwl_lq_sta *lq_sta,
				  struct rs_rate *rate)
{
	if (is_legacy(rate))
		return lq_sta->active_legacy_rate;
	else if (is_siso(rate))
		return lq_sta->active_siso_rate;
	else if (is_mimo2(rate))
		return lq_sta->active_mimo2_rate;

	WARN_ON_ONCE(1);
	return 0;
}