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
struct fsl_pwm_chip {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_FMS ; 
 int FTM_FMS_WPEN ; 
 int /*<<< orphan*/  FTM_MODE ; 
 int /*<<< orphan*/  FTM_MODE_WPDIS ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftm_clear_write_protection(struct fsl_pwm_chip *fpc)
{
	u32 val;

	regmap_read(fpc->regmap, FTM_FMS, &val);
	if (val & FTM_FMS_WPEN)
		regmap_update_bits(fpc->regmap, FTM_MODE, FTM_MODE_WPDIS,
				   FTM_MODE_WPDIS);
}