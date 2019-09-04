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
struct tc_configuration {int /*<<< orphan*/  desc_credits_max; } ;
struct ixgbe_dcb_config {struct tc_configuration* tc_config; } ;

/* Variables and functions */
 int MAX_TRAFFIC_CLASS ; 

void ixgbe_dcb_unpack_max(struct ixgbe_dcb_config *cfg, u16 *max)
{
	struct tc_configuration *tc_config = &cfg->tc_config[0];
	int tc;

	for (tc = 0; tc < MAX_TRAFFIC_CLASS; tc++)
		max[tc] = tc_config[tc].desc_credits_max;
}