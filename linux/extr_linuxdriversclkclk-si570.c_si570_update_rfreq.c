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
struct clk_si570 {int n1; int rfreq; scalar_t__ div_offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int RFREQ_37_32_MASK ; 
 scalar_t__ SI570_REG_N1_RFREQ0 ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si570_update_rfreq(struct clk_si570 *data)
{
	u8 reg[5];

	reg[0] = ((data->n1 - 1) << 6) |
		((data->rfreq >> 32) & RFREQ_37_32_MASK);
	reg[1] = (data->rfreq >> 24) & 0xff;
	reg[2] = (data->rfreq >> 16) & 0xff;
	reg[3] = (data->rfreq >> 8) & 0xff;
	reg[4] = data->rfreq & 0xff;

	return regmap_bulk_write(data->regmap, SI570_REG_N1_RFREQ0 +
			data->div_offset, reg, ARRAY_SIZE(reg));
}