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
struct pwm_device {int dummy; } ;
struct fsl_pwm_chip {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_OUTMASK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool fsl_pwm_is_any_pwm_enabled(struct fsl_pwm_chip *fpc,
				       struct pwm_device *pwm)
{
	u32 val;

	regmap_read(fpc->regmap, FTM_OUTMASK, &val);
	if (~val & 0xFF)
		return true;
	else
		return false;
}