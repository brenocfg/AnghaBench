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
typedef  int uint32_t ;
struct qib_devdata {int dummy; } ;
struct dds_init {int* reg_vals; } ;

/* Variables and functions */
 int DDS_REG_MAP ; 
 int /*<<< orphan*/  EPB_LOC (int /*<<< orphan*/ ,int,int) ; 
 int NUM_DDS_REGS ; 
 int ibsd_mod_allchnls (struct qib_devdata*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int set_dds_vals(struct qib_devdata *dd, struct dds_init *ddi)
{
	int ret;
	int idx, reg, data;
	uint32_t regmap;

	regmap = DDS_REG_MAP;
	for (idx = 0; idx < NUM_DDS_REGS; ++idx) {
		reg = (regmap & 0xF);
		regmap >>= 4;
		data = ddi->reg_vals[idx];
		/* Vendor says RMW not needed for these regs, use 0xFF mask */
		ret = ibsd_mod_allchnls(dd, EPB_LOC(0, 9, reg), data, 0xFF);
		if (ret < 0)
			break;
	}
	return ret;
}