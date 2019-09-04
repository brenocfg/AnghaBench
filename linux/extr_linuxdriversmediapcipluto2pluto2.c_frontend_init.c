#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pluto {TYPE_4__* fe; int /*<<< orphan*/  dvb_adapter; TYPE_1__* pdev; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_8__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* release ) (TYPE_4__*) ;TYPE_2__ tuner_ops; } ;
struct TYPE_10__ {TYPE_3__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dvb_register_frontend (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  lg_tdtpe001p_tuner_set_params ; 
 int /*<<< orphan*/  pluto2_fe_config ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 TYPE_4__* tda10046_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int frontend_init(struct pluto *pluto)
{
	int ret;

	pluto->fe = tda10046_attach(&pluto2_fe_config, &pluto->i2c_adap);
	if (!pluto->fe) {
		dev_err(&pluto->pdev->dev, "could not attach frontend\n");
		return -ENODEV;
	}
	pluto->fe->ops.tuner_ops.set_params = lg_tdtpe001p_tuner_set_params;

	ret = dvb_register_frontend(&pluto->dvb_adapter, pluto->fe);
	if (ret < 0) {
		if (pluto->fe->ops.release)
			pluto->fe->ops.release(pluto->fe);
		return ret;
	}

	return 0;
}