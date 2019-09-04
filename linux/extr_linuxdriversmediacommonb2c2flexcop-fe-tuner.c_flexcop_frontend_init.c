#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {int /*<<< orphan*/  init_state; TYPE_5__* fe; int /*<<< orphan*/  dvb_adapter; int /*<<< orphan*/  dev_type; TYPE_1__* fc_i2c_adap; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_2__ info; } ;
struct TYPE_12__ {TYPE_3__ ops; } ;
struct TYPE_11__ {scalar_t__ (* attach ) (struct flexcop_device*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FC_STATE_FE_INIT ; 
 int /*<<< orphan*/  FC_UNK ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_5__*) ; 
 scalar_t__ dvb_register_frontend (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  err (char*) ; 
 TYPE_4__* flexcop_frontends ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct flexcop_device*,int /*<<< orphan*/ *) ; 

int flexcop_frontend_init(struct flexcop_device *fc)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(flexcop_frontends); i++) {
		if (!flexcop_frontends[i].attach)
			continue;
		/* type needs to be set before, because of some workarounds
		 * done based on the probed card type */
		fc->dev_type = flexcop_frontends[i].type;
		if (flexcop_frontends[i].attach(fc, &fc->fc_i2c_adap[0].i2c_adap))
			goto fe_found;
		/* Clean up partially attached frontend */
		if (fc->fe) {
			dvb_frontend_detach(fc->fe);
			fc->fe = NULL;
		}
	}
	fc->dev_type = FC_UNK;
	err("no frontend driver found for this B2C2/FlexCop adapter");
	return -ENODEV;

fe_found:
	info("found '%s' .", fc->fe->ops.info.name);
	if (dvb_register_frontend(&fc->dvb_adapter, fc->fe)) {
		err("frontend registration failed!");
		dvb_frontend_detach(fc->fe);
		fc->fe = NULL;
		return -EINVAL;
	}
	fc->init_state |= FC_STATE_FE_INIT;
	return 0;
}