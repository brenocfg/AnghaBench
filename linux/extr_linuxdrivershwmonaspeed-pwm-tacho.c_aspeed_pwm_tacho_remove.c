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
struct aspeed_pwm_tacho_data {int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_pwm_tacho_remove(void *data)
{
	struct aspeed_pwm_tacho_data *priv = data;

	reset_control_assert(priv->rst);
}