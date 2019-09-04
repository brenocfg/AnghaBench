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
typedef  int /*<<< orphan*/  u8 ;
struct xc2028_ctrl {int dummy; } ;
struct xc2028_config {struct xc2028_ctrl* ctrl; int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/ * i2c_adap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * frontend; } ;
struct vb2_dvb_frontend {TYPE_1__ dvb; } ;
struct dvb_frontend {int dummy; } ;
struct cx8802_dev {TYPE_2__* core; int /*<<< orphan*/  frontends; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cx88_setup_xc3028 (TYPE_2__*,struct xc2028_ctrl*) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xc2028_config*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct vb2_dvb_frontend* vb2_dvb_get_frontend (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xc2028_attach ; 

__attribute__((used)) static int attach_xc3028(u8 addr, struct cx8802_dev *dev)
{
	struct dvb_frontend *fe;
	struct vb2_dvb_frontend *fe0 = NULL;
	struct xc2028_ctrl ctl;
	struct xc2028_config cfg = {
		.i2c_adap  = &dev->core->i2c_adap,
		.i2c_addr  = addr,
		.ctrl      = &ctl,
	};

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&dev->frontends, 1);
	if (!fe0)
		return -EINVAL;

	if (!fe0->dvb.frontend) {
		pr_err("dvb frontend not attached. Can't attach xc3028\n");
		return -EINVAL;
	}

	/*
	 * Some xc3028 devices may be hidden by an I2C gate. This is known
	 * to happen with some s5h1409-based devices.
	 * Now that I2C gate is open, sets up xc3028 configuration
	 */
	cx88_setup_xc3028(dev->core, &ctl);

	fe = dvb_attach(xc2028_attach, fe0->dvb.frontend, &cfg);
	if (!fe) {
		pr_err("xc3028 attach failed\n");
		dvb_frontend_detach(fe0->dvb.frontend);
		dvb_unregister_frontend(fe0->dvb.frontend);
		fe0->dvb.frontend = NULL;
		return -EINVAL;
	}

	pr_info("xc3028 attached\n");

	return 0;
}