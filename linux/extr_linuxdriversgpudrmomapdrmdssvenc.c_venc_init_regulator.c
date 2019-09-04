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
struct venc_device {struct regulator* vdda_dac_reg; TYPE_1__* pdev; } ;
struct regulator {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int venc_init_regulator(struct venc_device *venc)
{
	struct regulator *vdda_dac;

	if (venc->vdda_dac_reg != NULL)
		return 0;

	vdda_dac = devm_regulator_get(&venc->pdev->dev, "vdda");
	if (IS_ERR(vdda_dac)) {
		if (PTR_ERR(vdda_dac) != -EPROBE_DEFER)
			DSSERR("can't get VDDA_DAC regulator\n");
		return PTR_ERR(vdda_dac);
	}

	venc->vdda_dac_reg = vdda_dac;

	return 0;
}