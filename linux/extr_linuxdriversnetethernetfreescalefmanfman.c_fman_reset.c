#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct fman {TYPE_2__* fpm_regs; TYPE_1__* state; } ;
struct TYPE_6__ {int major; } ;
struct TYPE_5__ {int /*<<< orphan*/  fm_rstc; } ;
struct TYPE_4__ {TYPE_3__ rev_info; } ;

/* Variables and functions */
 int EBUSY ; 
 int FPM_RSTC_FM_RESET ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fman_reset(struct fman *fman)
{
	u32 count;
	int err = 0;

	if (fman->state->rev_info.major < 6) {
		iowrite32be(FPM_RSTC_FM_RESET, &fman->fpm_regs->fm_rstc);
		/* Wait for reset completion */
		count = 100;
		do {
			udelay(1);
		} while (((ioread32be(&fman->fpm_regs->fm_rstc)) &
			 FPM_RSTC_FM_RESET) && --count);
		if (count == 0)
			err = -EBUSY;

		goto _return;
	} else {
#ifdef CONFIG_PPC
		struct device_node *guts_node;
		struct ccsr_guts __iomem *guts_regs;
		u32 devdisr2, reg;

		/* Errata A007273 */
		guts_node =
			of_find_compatible_node(NULL, NULL,
						"fsl,qoriq-device-config-2.0");
		if (!guts_node) {
			dev_err(fman->dev, "%s: Couldn't find guts node\n",
				__func__);
			goto guts_node;
		}

		guts_regs = of_iomap(guts_node, 0);
		if (!guts_regs) {
			dev_err(fman->dev, "%s: Couldn't map %pOF regs\n",
				__func__, guts_node);
			goto guts_regs;
		}
#define FMAN1_ALL_MACS_MASK	0xFCC00000
#define FMAN2_ALL_MACS_MASK	0x000FCC00
		/* Read current state */
		devdisr2 = ioread32be(&guts_regs->devdisr2);
		if (fman->dts_params.id == 0)
			reg = devdisr2 & ~FMAN1_ALL_MACS_MASK;
		else
			reg = devdisr2 & ~FMAN2_ALL_MACS_MASK;

		/* Enable all MACs */
		iowrite32be(reg, &guts_regs->devdisr2);
#endif

		/* Perform FMan reset */
		iowrite32be(FPM_RSTC_FM_RESET, &fman->fpm_regs->fm_rstc);

		/* Wait for reset completion */
		count = 100;
		do {
			udelay(1);
		} while (((ioread32be(&fman->fpm_regs->fm_rstc)) &
			 FPM_RSTC_FM_RESET) && --count);
		if (count == 0) {
#ifdef CONFIG_PPC
			iounmap(guts_regs);
			of_node_put(guts_node);
#endif
			err = -EBUSY;
			goto _return;
		}
#ifdef CONFIG_PPC

		/* Restore devdisr2 value */
		iowrite32be(devdisr2, &guts_regs->devdisr2);

		iounmap(guts_regs);
		of_node_put(guts_node);
#endif

		goto _return;

#ifdef CONFIG_PPC
guts_regs:
		of_node_put(guts_node);
guts_node:
		dev_dbg(fman->dev, "%s: Didn't perform FManV3 reset due to Errata A007273!\n",
			__func__);
#endif
	}
_return:
	return err;
}