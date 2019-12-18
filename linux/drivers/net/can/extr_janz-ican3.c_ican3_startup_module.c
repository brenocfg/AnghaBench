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
struct ican3_dev {int num; int /*<<< orphan*/  ndev; TYPE_1__* ctrl; int /*<<< orphan*/  fwtype; int /*<<< orphan*/  fwinfo; scalar_t__ dpm; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_enable; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ FIRMWARE_STAMP ; 
 int /*<<< orphan*/  ICAN3_FWTYPE_CAL_CANOPEN ; 
 int /*<<< orphan*/  ICAN3_FWTYPE_ICANOS ; 
 int /*<<< orphan*/  ican3_init_fast_host_interface (struct ican3_dev*) ; 
 int /*<<< orphan*/  ican3_init_new_host_interface (struct ican3_dev*) ; 
 int ican3_msg_connect (struct ican3_dev*) ; 
 int ican3_msg_fasthostif (struct ican3_dev*) ; 
 int ican3_msg_newhostif (struct ican3_dev*) ; 
 int ican3_reset_module (struct ican3_dev*) ; 
 int ican3_set_buserror (struct ican3_dev*,int) ; 
 int ican3_set_id_filter (struct ican3_dev*,int) ; 
 int ican3_set_termination (struct ican3_dev*,int) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ican3_startup_module(struct ican3_dev *mod)
{
	int ret;

	ret = ican3_reset_module(mod);
	if (ret) {
		netdev_err(mod->ndev, "unable to reset module\n");
		return ret;
	}

	/* detect firmware */
	memcpy_fromio(mod->fwinfo, mod->dpm + FIRMWARE_STAMP, sizeof(mod->fwinfo) - 1);
	if (strncmp(mod->fwinfo, "JANZ-ICAN3", 10)) {
		netdev_err(mod->ndev, "ICAN3 not detected (found %s)\n", mod->fwinfo);
		return -ENODEV;
	}
	if (strstr(mod->fwinfo, "CAL/CANopen"))
		mod->fwtype = ICAN3_FWTYPE_CAL_CANOPEN;
	else
		mod->fwtype = ICAN3_FWTYPE_ICANOS;

	/* re-enable interrupts so we can send messages */
	iowrite8(1 << mod->num, &mod->ctrl->int_enable);

	ret = ican3_msg_connect(mod);
	if (ret) {
		netdev_err(mod->ndev, "unable to connect to module\n");
		return ret;
	}

	ican3_init_new_host_interface(mod);
	ret = ican3_msg_newhostif(mod);
	if (ret) {
		netdev_err(mod->ndev, "unable to switch to new-style interface\n");
		return ret;
	}

	/* default to "termination on" */
	ret = ican3_set_termination(mod, true);
	if (ret) {
		netdev_err(mod->ndev, "unable to enable termination\n");
		return ret;
	}

	/* default to "bus errors enabled" */
	ret = ican3_set_buserror(mod, 1);
	if (ret) {
		netdev_err(mod->ndev, "unable to set bus-error\n");
		return ret;
	}

	ican3_init_fast_host_interface(mod);
	ret = ican3_msg_fasthostif(mod);
	if (ret) {
		netdev_err(mod->ndev, "unable to switch to fast host interface\n");
		return ret;
	}

	ret = ican3_set_id_filter(mod, true);
	if (ret) {
		netdev_err(mod->ndev, "unable to set acceptance filter\n");
		return ret;
	}

	return 0;
}