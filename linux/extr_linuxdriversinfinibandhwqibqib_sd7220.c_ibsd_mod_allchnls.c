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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int EPB_ADDR_SHF ; 
 int EPB_GLOBAL_WR ; 
 unsigned int EPB_IB_QUAD0_CS_SHF ; 
 int /*<<< orphan*/  IB_7220_SERDES ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int,int,int,...) ; 
 int qib_sd7220_reg_mod (struct qib_devdata*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int ibsd_mod_allchnls(struct qib_devdata *dd, int loc, int val,
			     int mask)
{
	int ret = -1;
	int chnl;

	if (loc & EPB_GLOBAL_WR) {
		/*
		 * Our caller has assured us that we can set all four
		 * channels at once. Trust that. If mask is not 0xFF,
		 * we will read the _specified_ channel for our starting
		 * value.
		 */
		loc |= (1U << EPB_IB_QUAD0_CS_SHF);
		chnl = (loc >> (4 + EPB_ADDR_SHF)) & 7;
		if (mask != 0xFF) {
			ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
						 loc & ~EPB_GLOBAL_WR, 0, 0);
			if (ret < 0) {
				int sloc = loc >> EPB_ADDR_SHF;

				qib_dev_err(dd,
					"pre-read failed: elt %d, addr 0x%X, chnl %d\n",
					(sloc & 0xF),
					(sloc >> 9) & 0x3f, chnl);
				return ret;
			}
			val = (ret & ~mask) | (val & mask);
		}
		loc &=  ~(7 << (4+EPB_ADDR_SHF));
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, val, 0xFF);
		if (ret < 0) {
			int sloc = loc >> EPB_ADDR_SHF;

			qib_dev_err(dd,
				"Global WR failed: elt %d, addr 0x%X, val %02X\n",
				(sloc & 0xF), (sloc >> 9) & 0x3f, val);
		}
		return ret;
	}
	/* Clear "channel" and set CS so we can simply iterate */
	loc &=  ~(7 << (4+EPB_ADDR_SHF));
	loc |= (1U << EPB_IB_QUAD0_CS_SHF);
	for (chnl = 0; chnl < 4; ++chnl) {
		int cloc = loc | (chnl << (4+EPB_ADDR_SHF));

		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, cloc, val, mask);
		if (ret < 0) {
			int sloc = loc >> EPB_ADDR_SHF;

			qib_dev_err(dd,
				"Write failed: elt %d, addr 0x%X, chnl %d, val 0x%02X, mask 0x%02X\n",
				(sloc & 0xF), (sloc >> 9) & 0x3f, chnl,
				val & 0xFF, mask & 0xFF);
			break;
		}
	}
	return ret;
}