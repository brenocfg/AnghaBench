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
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct mt6397_chip {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsel_reg; } ;
struct TYPE_5__ {int vselctrl_mask; int /*<<< orphan*/  vselon_reg; TYPE_1__ desc; scalar_t__ vselctrl_reg; } ;

/* Variables and functions */
 int EIO ; 
 int MT6397_MAX_REGULATOR ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct mt6397_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__* mt6397_regulators ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static int mt6397_set_buck_vosel_reg(struct platform_device *pdev)
{
	struct mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);
	int i;
	u32 regval;

	for (i = 0; i < MT6397_MAX_REGULATOR; i++) {
		if (mt6397_regulators[i].vselctrl_reg) {
			if (regmap_read(mt6397->regmap,
				mt6397_regulators[i].vselctrl_reg,
				&regval) < 0) {
				dev_err(&pdev->dev,
					"Failed to read buck ctrl\n");
				return -EIO;
			}

			if (regval & mt6397_regulators[i].vselctrl_mask) {
				mt6397_regulators[i].desc.vsel_reg =
				mt6397_regulators[i].vselon_reg;
			}
		}
	}

	return 0;
}