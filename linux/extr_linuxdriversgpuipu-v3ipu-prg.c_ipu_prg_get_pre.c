#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ipu_prg {int id; int /*<<< orphan*/  dev; int /*<<< orphan*/  iomuxc_gpr; TYPE_1__* chan; int /*<<< orphan*/ * pres; } ;
struct TYPE_2__ {int used_pre; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUXC_GPR5 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ipu_pre_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ipu_prg_get_pre(struct ipu_prg *prg, int prg_chan)
{
	int i, ret;

	/* channel 0 is special as it is hardwired to one of the PREs */
	if (prg_chan == 0) {
		ret = ipu_pre_get(prg->pres[0]);
		if (ret)
			goto fail;
		prg->chan[prg_chan].used_pre = 0;
		return 0;
	}

	for (i = 1; i < 3; i++) {
		ret = ipu_pre_get(prg->pres[i]);
		if (!ret) {
			u32 val, mux;
			int shift;

			prg->chan[prg_chan].used_pre = i;

			/* configure the PRE to PRG channel mux */
			shift = (i == 1) ? 12 : 14;
			mux = (prg->id << 1) | (prg_chan - 1);
			regmap_update_bits(prg->iomuxc_gpr, IOMUXC_GPR5,
					   0x3 << shift, mux << shift);

			/* check other mux, must not point to same channel */
			shift = (i == 1) ? 14 : 12;
			regmap_read(prg->iomuxc_gpr, IOMUXC_GPR5, &val);
			if (((val >> shift) & 0x3) == mux) {
				regmap_update_bits(prg->iomuxc_gpr, IOMUXC_GPR5,
						   0x3 << shift,
						   (mux ^ 0x1) << shift);
			}

			return 0;
		}
	}

fail:
	dev_err(prg->dev, "could not get PRE for PRG chan %d", prg_chan);
	return ret;
}