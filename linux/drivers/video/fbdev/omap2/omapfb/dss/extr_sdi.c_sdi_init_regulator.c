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
struct TYPE_4__ {struct regulator* vdds_sdi_reg; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ sdi ; 

__attribute__((used)) static int sdi_init_regulator(void)
{
	struct regulator *vdds_sdi;

	if (sdi.vdds_sdi_reg)
		return 0;

	vdds_sdi = devm_regulator_get(&sdi.pdev->dev, "vdds_sdi");
	if (IS_ERR(vdds_sdi)) {
		if (PTR_ERR(vdds_sdi) != -EPROBE_DEFER)
			DSSERR("can't get VDDS_SDI regulator\n");
		return PTR_ERR(vdds_sdi);
	}

	sdi.vdds_sdi_reg = vdds_sdi;

	return 0;
}