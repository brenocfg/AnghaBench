#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator {int dummy; } ;
struct TYPE_4__ {struct regulator* vdda_reg; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ hdmi ; 

__attribute__((used)) static int hdmi_init_regulator(void)
{
	struct regulator *reg;

	if (hdmi.vdda_reg != NULL)
		return 0;

	reg = devm_regulator_get(&hdmi.pdev->dev, "vdda");
	if (IS_ERR(reg)) {
		DSSERR("can't get VDDA regulator\n");
		return PTR_ERR(reg);
	}

	hdmi.vdda_reg = reg;

	return 0;
}