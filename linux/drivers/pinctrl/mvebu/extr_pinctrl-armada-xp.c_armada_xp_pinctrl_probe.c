#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {struct mvebu_pinctrl_soc_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mvebu_pinctrl_soc_info {unsigned int variant; int /*<<< orphan*/  nmodes; void* ngpioranges; TYPE_2__* gpioranges; void* modes; void* ncontrols; TYPE_2__* controls; } ;
struct TYPE_13__ {int /*<<< orphan*/  npins; } ;

/* Variables and functions */
 void* ARRAY_SIZE (TYPE_2__*) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MVEBU_MPPS_PER_REG ; 
#define  V_98DX3236 133 
#define  V_98DX3336 132 
#define  V_98DX4251 131 
#define  V_MV78230 130 
#define  V_MV78260 129 
#define  V_MV78460 128 
 void* armada_xp_mpp_modes ; 
 struct mvebu_pinctrl_soc_info armada_xp_pinctrl_info ; 
 int /*<<< orphan*/  armada_xp_pinctrl_of_match ; 
 int /*<<< orphan*/  devm_kmalloc_array (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpp_saved_regs ; 
 TYPE_2__* mv78230_mpp_controls ; 
 TYPE_2__* mv78230_mpp_gpio_ranges ; 
 TYPE_2__* mv78260_mpp_controls ; 
 TYPE_2__* mv78260_mpp_gpio_ranges ; 
 TYPE_2__* mv78460_mpp_controls ; 
 TYPE_2__* mv78460_mpp_gpio_ranges ; 
 TYPE_2__* mv98dx3236_mpp_controls ; 
 TYPE_2__* mv98dx3236_mpp_gpio_ranges ; 
 void* mv98dx3236_mpp_modes ; 
 int mvebu_pinctrl_simple_mmio_probe (struct platform_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int armada_xp_pinctrl_probe(struct platform_device *pdev)
{
	struct mvebu_pinctrl_soc_info *soc = &armada_xp_pinctrl_info;
	const struct of_device_id *match =
		of_match_device(armada_xp_pinctrl_of_match, &pdev->dev);
	int nregs;

	if (!match)
		return -ENODEV;

	soc->variant = (unsigned) match->data & 0xff;

	switch (soc->variant) {
	case V_MV78230:
		soc->controls = mv78230_mpp_controls;
		soc->ncontrols = ARRAY_SIZE(mv78230_mpp_controls);
		soc->modes = armada_xp_mpp_modes;
		/* We don't necessarily want the full list of the
		 * armada_xp_mpp_modes, but only the first 'n' ones
		 * that are available on this SoC */
		soc->nmodes = mv78230_mpp_controls[0].npins;
		soc->gpioranges = mv78230_mpp_gpio_ranges;
		soc->ngpioranges = ARRAY_SIZE(mv78230_mpp_gpio_ranges);
		break;
	case V_MV78260:
		soc->controls = mv78260_mpp_controls;
		soc->ncontrols = ARRAY_SIZE(mv78260_mpp_controls);
		soc->modes = armada_xp_mpp_modes;
		/* We don't necessarily want the full list of the
		 * armada_xp_mpp_modes, but only the first 'n' ones
		 * that are available on this SoC */
		soc->nmodes = mv78260_mpp_controls[0].npins;
		soc->gpioranges = mv78260_mpp_gpio_ranges;
		soc->ngpioranges = ARRAY_SIZE(mv78260_mpp_gpio_ranges);
		break;
	case V_MV78460:
		soc->controls = mv78460_mpp_controls;
		soc->ncontrols = ARRAY_SIZE(mv78460_mpp_controls);
		soc->modes = armada_xp_mpp_modes;
		/* We don't necessarily want the full list of the
		 * armada_xp_mpp_modes, but only the first 'n' ones
		 * that are available on this SoC */
		soc->nmodes = mv78460_mpp_controls[0].npins;
		soc->gpioranges = mv78460_mpp_gpio_ranges;
		soc->ngpioranges = ARRAY_SIZE(mv78460_mpp_gpio_ranges);
		break;
	case V_98DX3236:
	case V_98DX3336:
	case V_98DX4251:
		/* fall-through */
		soc->controls = mv98dx3236_mpp_controls;
		soc->ncontrols = ARRAY_SIZE(mv98dx3236_mpp_controls);
		soc->modes = mv98dx3236_mpp_modes;
		soc->nmodes = mv98dx3236_mpp_controls[0].npins;
		soc->gpioranges = mv98dx3236_mpp_gpio_ranges;
		soc->ngpioranges = ARRAY_SIZE(mv98dx3236_mpp_gpio_ranges);
		break;
	}

	nregs = DIV_ROUND_UP(soc->nmodes, MVEBU_MPPS_PER_REG);

	mpp_saved_regs = devm_kmalloc_array(&pdev->dev, nregs, sizeof(u32),
					    GFP_KERNEL);
	if (!mpp_saved_regs)
		return -ENOMEM;

	pdev->dev.platform_data = soc;

	return mvebu_pinctrl_simple_mmio_probe(pdev);
}