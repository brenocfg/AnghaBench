#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct aspeed_p2a_ctrl {int /*<<< orphan*/  regmap; TYPE_2__* config; } ;
struct TYPE_4__ {TYPE_1__* regions; } ;
struct TYPE_3__ {int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int P2A_REGION_COUNT ; 
 int /*<<< orphan*/  SCU2C ; 
 int /*<<< orphan*/  aspeed_p2a_disable_bridge (struct aspeed_p2a_ctrl*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_p2a_disable_all(struct aspeed_p2a_ctrl *p2a_ctrl)
{
	int i;
	u32 value = 0;

	for (i = 0; i < P2A_REGION_COUNT; i++)
		value |= p2a_ctrl->config->regions[i].bit;

	regmap_update_bits(p2a_ctrl->regmap, SCU2C, value, value);

	/* Disable the bridge. */
	aspeed_p2a_disable_bridge(p2a_ctrl);
}