#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int TRAINIG_AUX_RD_INTERVAL; } ;
union training_aux_rd_interval {TYPE_3__ bits; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  training_rd_interval ;
struct TYPE_4__ {scalar_t__ raw; } ;
struct TYPE_5__ {TYPE_1__ dpcd_rev; } ;
struct dc_link {TYPE_2__ dpcd_caps; } ;

/* Variables and functions */
 scalar_t__ DPCD_REV_12 ; 
 int /*<<< orphan*/  DP_TRAINING_AUX_RD_INTERVAL ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union training_aux_rd_interval*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t get_training_aux_rd_interval(
	struct dc_link *link,
	uint32_t default_wait_in_micro_secs)
{
	union training_aux_rd_interval training_rd_interval;

	memset(&training_rd_interval, 0, sizeof(training_rd_interval));

	/* overwrite the delay if rev > 1.1*/
	if (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_12) {
		/* DP 1.2 or later - retrieve delay through
		 * "DPCD_ADDR_TRAINING_AUX_RD_INTERVAL" register */
		core_link_read_dpcd(
			link,
			DP_TRAINING_AUX_RD_INTERVAL,
			(uint8_t *)&training_rd_interval,
			sizeof(training_rd_interval));

		if (training_rd_interval.bits.TRAINIG_AUX_RD_INTERVAL)
			default_wait_in_micro_secs = training_rd_interval.bits.TRAINIG_AUX_RD_INTERVAL * 4000;
	}

	return default_wait_in_micro_secs;
}