#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dc_link_settings {scalar_t__ link_rate; scalar_t__ lane_count; scalar_t__ link_spread; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__ lane_count; scalar_t__ link_rate; scalar_t__ link_spread; } ;
struct dc_link {TYPE_5__ reported_link_cap; TYPE_4__* link_enc; } ;
struct TYPE_6__ {scalar_t__ IS_HBR3_CAPABLE; scalar_t__ IS_HBR2_CAPABLE; } ;
struct TYPE_7__ {TYPE_1__ bits; } ;
struct TYPE_8__ {TYPE_2__ flags; } ;
struct TYPE_9__ {TYPE_3__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  LANE_COUNT_FOUR ; 
 int /*<<< orphan*/  LINK_RATE_HIGH ; 
 scalar_t__ LINK_RATE_HIGH2 ; 
 scalar_t__ LINK_RATE_HIGH3 ; 
 int /*<<< orphan*/  LINK_SPREAD_05_DOWNSPREAD_30KHZ ; 

__attribute__((used)) static struct dc_link_settings get_max_link_cap(struct dc_link *link)
{
	/* Set Default link settings */
	struct dc_link_settings max_link_cap = {LANE_COUNT_FOUR, LINK_RATE_HIGH,
			LINK_SPREAD_05_DOWNSPREAD_30KHZ};

	/* Higher link settings based on feature supported */
	if (link->link_enc->features.flags.bits.IS_HBR2_CAPABLE)
		max_link_cap.link_rate = LINK_RATE_HIGH2;

	if (link->link_enc->features.flags.bits.IS_HBR3_CAPABLE)
		max_link_cap.link_rate = LINK_RATE_HIGH3;

	/* Lower link settings based on sink's link cap */
	if (link->reported_link_cap.lane_count < max_link_cap.lane_count)
		max_link_cap.lane_count =
				link->reported_link_cap.lane_count;
	if (link->reported_link_cap.link_rate < max_link_cap.link_rate)
		max_link_cap.link_rate =
				link->reported_link_cap.link_rate;
	if (link->reported_link_cap.link_spread <
			max_link_cap.link_spread)
		max_link_cap.link_spread =
				link->reported_link_cap.link_spread;
	return max_link_cap;
}