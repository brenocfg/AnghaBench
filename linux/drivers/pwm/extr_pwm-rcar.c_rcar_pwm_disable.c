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
struct rcar_pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_PWMCR ; 
 int /*<<< orphan*/  RCAR_PWMCR_EN0 ; 
 int /*<<< orphan*/  rcar_pwm_update (struct rcar_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_pwm_disable(struct rcar_pwm_chip *rp)
{
	rcar_pwm_update(rp, RCAR_PWMCR_EN0, 0, RCAR_PWMCR);
}