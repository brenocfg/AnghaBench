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
struct adxl372_state {int /*<<< orphan*/  regmap; } ;
typedef  enum adxl372_th_activity { ____Placeholder_adxl372_th_activity } adxl372_th_activity ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned char*) ; 
 unsigned char* adxl372_th_reg_high_addr ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,unsigned char,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adxl372_set_activity_threshold(struct adxl372_state *st,
					  enum adxl372_th_activity act,
					  bool ref_en, bool enable,
					  unsigned int threshold)
{
	unsigned char buf[6];
	unsigned char th_reg_high_val, th_reg_low_val, th_reg_high_addr;

	/* scale factor is 100 mg/code */
	th_reg_high_val = (threshold / 100) >> 3;
	th_reg_low_val = ((threshold / 100) << 5) | (ref_en << 1) | enable;
	th_reg_high_addr = adxl372_th_reg_high_addr[act];

	buf[0] = th_reg_high_val;
	buf[1] = th_reg_low_val;
	buf[2] = th_reg_high_val;
	buf[3] = th_reg_low_val;
	buf[4] = th_reg_high_val;
	buf[5] = th_reg_low_val;

	return regmap_bulk_write(st->regmap, th_reg_high_addr,
				 buf, ARRAY_SIZE(buf));
}