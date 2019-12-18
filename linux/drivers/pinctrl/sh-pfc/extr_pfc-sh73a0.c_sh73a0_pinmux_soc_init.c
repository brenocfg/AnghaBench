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
struct sh_pfc {int /*<<< orphan*/  dev; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct sh_pfc* driver_data; int /*<<< orphan*/ * init_data; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  sh73a0_vccq_mc0_desc ; 
 int /*<<< orphan*/  sh73a0_vccq_mc0_init_data ; 

__attribute__((used)) static int sh73a0_pinmux_soc_init(struct sh_pfc *pfc)
{
	struct regulator_config cfg = { };
	struct regulator_dev *vccq;
	int ret;

	cfg.dev = pfc->dev;
	cfg.init_data = &sh73a0_vccq_mc0_init_data;
	cfg.driver_data = pfc;

	vccq = devm_regulator_register(pfc->dev, &sh73a0_vccq_mc0_desc, &cfg);
	if (IS_ERR(vccq)) {
		ret = PTR_ERR(vccq);
		dev_err(pfc->dev, "Failed to register VCCQ MC0 regulator: %d\n",
			ret);
		return ret;
	}

	return 0;
}