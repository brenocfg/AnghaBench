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
struct kv_pl {scalar_t__ sclk; scalar_t__ vddc_index; scalar_t__ ds_divider_index; scalar_t__ force_nbp_state; } ;

/* Variables and functions */

__attribute__((used)) static inline bool kv_are_power_levels_equal(const struct kv_pl *kv_cpl1,
						const struct kv_pl *kv_cpl2)
{
	return ((kv_cpl1->sclk == kv_cpl2->sclk) &&
		  (kv_cpl1->vddc_index == kv_cpl2->vddc_index) &&
		  (kv_cpl1->ds_divider_index == kv_cpl2->ds_divider_index) &&
		  (kv_cpl1->force_nbp_state == kv_cpl2->force_nbp_state));
}