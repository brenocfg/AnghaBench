#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_3__ {unsigned int pin; unsigned char pupd_offset; unsigned char r0_offset; unsigned char r1_offset; int /*<<< orphan*/  r1_bit; int /*<<< orphan*/  r0_bit; int /*<<< orphan*/  pupd_bit; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
#define  MTK_PUPD_SET_R1R0_00 131 
#define  MTK_PUPD_SET_R1R0_01 130 
#define  MTK_PUPD_SET_R1R0_10 129 
#define  MTK_PUPD_SET_R1R0_11 128 
 int /*<<< orphan*/  regmap_write (struct regmap*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* spec_pupd ; 

__attribute__((used)) static int spec_pull_set(struct regmap *regmap, unsigned int pin,
		unsigned char align, bool isup, unsigned int r1r0)
{
	unsigned int i;
	unsigned int reg_pupd, reg_set_r0, reg_set_r1;
	unsigned int reg_rst_r0, reg_rst_r1;
	bool find = false;

	for (i = 0; i < ARRAY_SIZE(spec_pupd); i++) {
		if (pin == spec_pupd[i].pin) {
			find = true;
			break;
		}
	}

	if (!find)
		return -EINVAL;

	if (isup)
		reg_pupd = spec_pupd[i].pupd_offset + align;
	else
		reg_pupd = spec_pupd[i].pupd_offset + (align << 1);

	regmap_write(regmap, reg_pupd, spec_pupd[i].pupd_bit);

	reg_set_r0 = spec_pupd[i].r0_offset + align;
	reg_rst_r0 = spec_pupd[i].r0_offset + (align << 1);
	reg_set_r1 = spec_pupd[i].r1_offset + align;
	reg_rst_r1 = spec_pupd[i].r1_offset + (align << 1);

	switch (r1r0) {
	case MTK_PUPD_SET_R1R0_00:
		regmap_write(regmap, reg_rst_r0, spec_pupd[i].r0_bit);
		regmap_write(regmap, reg_rst_r1, spec_pupd[i].r1_bit);
		break;
	case MTK_PUPD_SET_R1R0_01:
		regmap_write(regmap, reg_set_r0, spec_pupd[i].r0_bit);
		regmap_write(regmap, reg_rst_r1, spec_pupd[i].r1_bit);
		break;
	case MTK_PUPD_SET_R1R0_10:
		regmap_write(regmap, reg_rst_r0, spec_pupd[i].r0_bit);
		regmap_write(regmap, reg_set_r1, spec_pupd[i].r1_bit);
		break;
	case MTK_PUPD_SET_R1R0_11:
		regmap_write(regmap, reg_set_r0, spec_pupd[i].r0_bit);
		regmap_write(regmap, reg_set_r1, spec_pupd[i].r1_bit);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}