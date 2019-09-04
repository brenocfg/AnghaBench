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
struct rpi_poe_fan_ctx {int rpi_poe_fan_max_state; unsigned long* rpi_poe_fan_cooling_levels; int rpi_poe_fan_state; } ;

/* Variables and functions */

__attribute__((used)) static void rpi_poe_fan_update_state(struct rpi_poe_fan_ctx *ctx,
				     unsigned long pwm)
{
	int i;

	for (i = 0; i < ctx->rpi_poe_fan_max_state; ++i)
		if (pwm < ctx->rpi_poe_fan_cooling_levels[i + 1])
			break;

	ctx->rpi_poe_fan_state = i;
}