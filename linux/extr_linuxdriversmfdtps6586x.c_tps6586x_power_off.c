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

/* Variables and functions */
 int /*<<< orphan*/  EXITSLREQ_BIT ; 
 int /*<<< orphan*/  SLEEP_MODE_BIT ; 
 int /*<<< orphan*/  TPS6586X_SUPPLYENE ; 
 scalar_t__ tps6586x_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps6586x_dev ; 
 int /*<<< orphan*/  tps6586x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tps6586x_power_off(void)
{
	if (tps6586x_clr_bits(tps6586x_dev, TPS6586X_SUPPLYENE, EXITSLREQ_BIT))
		return;

	tps6586x_set_bits(tps6586x_dev, TPS6586X_SUPPLYENE, SLEEP_MODE_BIT);
}