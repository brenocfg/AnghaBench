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
typedef  int u32 ;
struct rcar_pwm_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RCAR_PWMCNT ; 
 int RCAR_PWMCNT_CYC0_MASK ; 
 int RCAR_PWMCNT_PH0_MASK ; 
 int /*<<< orphan*/  RCAR_PWMCR ; 
 int /*<<< orphan*/  RCAR_PWMCR_EN0 ; 
 int rcar_pwm_read (struct rcar_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pwm_update (struct rcar_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_pwm_enable(struct rcar_pwm_chip *rp)
{
	u32 value;

	/* Don't enable the PWM device if CYC0 or PH0 is 0 */
	value = rcar_pwm_read(rp, RCAR_PWMCNT);
	if ((value & RCAR_PWMCNT_CYC0_MASK) == 0 ||
	    (value & RCAR_PWMCNT_PH0_MASK) == 0)
		return -EINVAL;

	rcar_pwm_update(rp, RCAR_PWMCR_EN0, RCAR_PWMCR_EN0, RCAR_PWMCR);

	return 0;
}