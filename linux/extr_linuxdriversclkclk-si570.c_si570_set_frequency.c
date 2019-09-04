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
struct clk_si570 {int n1; int hs_div; int /*<<< orphan*/  regmap; scalar_t__ div_offset; int /*<<< orphan*/  rfreq; } ;

/* Variables and functions */
 int HS_DIV_OFFSET ; 
 int HS_DIV_SHIFT ; 
 int N1_6_2_MASK ; 
 int SI570_CNTRL_NEWFREQ ; 
 int SI570_FREEZE_DCO ; 
 scalar_t__ SI570_REG_CONTROL ; 
 scalar_t__ SI570_REG_FREEZE_DCO ; 
 scalar_t__ SI570_REG_HS_N1 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int si570_calc_divs (unsigned long,struct clk_si570*,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  si570_update_rfreq (struct clk_si570*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int si570_set_frequency(struct clk_si570 *data, unsigned long frequency)
{
	int err;

	err = si570_calc_divs(frequency, data, &data->rfreq, &data->n1,
			&data->hs_div);
	if (err)
		return err;

	/*
	 * The DCO reg should be accessed with a read-modify-write operation
	 * per AN334
	 */
	regmap_write(data->regmap, SI570_REG_FREEZE_DCO, SI570_FREEZE_DCO);
	regmap_write(data->regmap, SI570_REG_HS_N1 + data->div_offset,
			((data->hs_div - HS_DIV_OFFSET) << HS_DIV_SHIFT) |
			(((data->n1 - 1) >> 2) & N1_6_2_MASK));
	si570_update_rfreq(data);
	regmap_write(data->regmap, SI570_REG_FREEZE_DCO, 0);
	regmap_write(data->regmap, SI570_REG_CONTROL, SI570_CNTRL_NEWFREQ);

	/* Applying a new frequency can take up to 10ms */
	usleep_range(10000, 12000);

	return 0;
}