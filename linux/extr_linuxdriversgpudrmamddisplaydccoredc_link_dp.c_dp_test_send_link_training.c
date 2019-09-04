#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dc_link_settings {scalar_t__ link_rate; scalar_t__ lane_count; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ link_rate; scalar_t__ lane_count; } ;
struct dc_link {TYPE_1__ verified_link_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TEST_LANE_COUNT ; 
 int /*<<< orphan*/  DP_TEST_LINK_RATE ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  dp_retrain_link_dp_test (struct dc_link*,struct dc_link_settings*,int) ; 

__attribute__((used)) static void dp_test_send_link_training(struct dc_link *link)
{
	struct dc_link_settings link_settings = {0};

	core_link_read_dpcd(
			link,
			DP_TEST_LANE_COUNT,
			(unsigned char *)(&link_settings.lane_count),
			1);
	core_link_read_dpcd(
			link,
			DP_TEST_LINK_RATE,
			(unsigned char *)(&link_settings.link_rate),
			1);

	/* Set preferred link settings */
	link->verified_link_cap.lane_count = link_settings.lane_count;
	link->verified_link_cap.link_rate = link_settings.link_rate;

	dp_retrain_link_dp_test(link, &link_settings, false);
}