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
struct TYPE_2__ {int is_branch_dev; } ;
struct dc_link {TYPE_1__ dpcd_caps; } ;

/* Variables and functions */

bool is_dp_active_dongle(const struct dc_link *link)
{
	return link->dpcd_caps.is_branch_dev;
}