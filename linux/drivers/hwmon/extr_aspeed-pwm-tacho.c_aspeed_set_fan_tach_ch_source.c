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
typedef  int u8 ;
typedef  int u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_PTCR_TACH_SOURCE ; 
 int /*<<< orphan*/  ASPEED_PTCR_TACH_SOURCE_EXT ; 
 int TACH_PWM_SOURCE_BIT01 (int) ; 
 int TACH_PWM_SOURCE_BIT2 (int) ; 
 int /*<<< orphan*/  TACH_PWM_SOURCE_MASK_BIT01 (int) ; 
 int /*<<< orphan*/  TACH_PWM_SOURCE_MASK_BIT2 (int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aspeed_set_fan_tach_ch_source(struct regmap *regmap, u8 fan_tach_ch,
					  u8 fan_tach_ch_source)
{
	u32 reg_value1 = ((fan_tach_ch_source & 0x3) <<
			  TACH_PWM_SOURCE_BIT01(fan_tach_ch));
	u32 reg_value2 = (((fan_tach_ch_source & 0x4) >> 2) <<
			  TACH_PWM_SOURCE_BIT2(fan_tach_ch));

	regmap_update_bits(regmap, ASPEED_PTCR_TACH_SOURCE,
			   TACH_PWM_SOURCE_MASK_BIT01(fan_tach_ch),
			   reg_value1);

	regmap_update_bits(regmap, ASPEED_PTCR_TACH_SOURCE_EXT,
			   TACH_PWM_SOURCE_MASK_BIT2(fan_tach_ch),
			   reg_value2);
}