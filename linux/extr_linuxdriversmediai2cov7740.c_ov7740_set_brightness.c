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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG13_AEC_EN ; 
 int /*<<< orphan*/  REG13_AGC_EN ; 
 int /*<<< orphan*/  REG_REG13 ; 
 int /*<<< orphan*/  REG_SGNSET ; 
 int /*<<< orphan*/  REG_YBRIGHT ; 
 int /*<<< orphan*/  SGNSET_YBRIGHT_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7740_set_brightness(struct regmap *regmap, int value)
{
	/* Turn off AEC/AGC */
	regmap_update_bits(regmap, REG_REG13, REG13_AEC_EN, 0);
	regmap_update_bits(regmap, REG_REG13, REG13_AGC_EN, 0);

	if (value >= 0) {
		regmap_write(regmap, REG_YBRIGHT, (unsigned char)value);
		regmap_update_bits(regmap, REG_SGNSET, SGNSET_YBRIGHT_MASK, 0);
	} else{
		regmap_write(regmap, REG_YBRIGHT, (unsigned char)(-value));
		regmap_update_bits(regmap, REG_SGNSET, SGNSET_YBRIGHT_MASK, 1);
	}

	return 0;
}