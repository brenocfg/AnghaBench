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
struct u132 {int hc_fminterval; int hc_control; int num_ports; int flags; TYPE_1__* platform_dev; } ;
struct TYPE_6__ {int a; int* portstatus; int status; int b; } ;
struct TYPE_5__ {void* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int FSMP (int) ; 
 void* HC_STATE_RUNNING ; 
 int OHCI_BLF ; 
 int const OHCI_CONTROL_INIT ; 
 int const OHCI_CTRL_BLE ; 
 int OHCI_CTRL_HCFS ; 
 int OHCI_CTRL_RWC ; 
 int OHCI_HCR ; 
 int OHCI_INTR_FNO ; 
 int OHCI_INTR_INIT ; 
 int OHCI_INTR_MIE ; 
 int OHCI_INTR_OC ; 
 int OHCI_INTR_RD ; 
 int OHCI_INTR_RHSC ; 
 int OHCI_INTR_SF ; 
 int OHCI_INTR_SO ; 
 int OHCI_INTR_UE ; 
 int OHCI_INTR_WDH ; 
 int OHCI_QUIRK_AMD756 ; 
 int OHCI_QUIRK_INITRESET ; 
 int OHCI_QUIRK_SUPERIO ; 
#define  OHCI_USB_OPER 130 
 int OHCI_USB_RESET ; 
#define  OHCI_USB_RESUME 129 
#define  OHCI_USB_SUSPEND 128 
 int RH_A_NOCP ; 
 int RH_A_NPS ; 
 int RH_A_OCPM ; 
 int RH_A_POTPGT ; 
 int RH_A_PSM ; 
 int RH_B_PPCM ; 
 int RH_HS_DRWE ; 
 int RH_HS_LPSC ; 
 int RH_PS_LSDA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ distrust_firmware ; 
 int ed_bulkhead ; 
 int ed_controlhead ; 
 int hcca ; 
 int /*<<< orphan*/  hcfs2string (int) ; 
 int intrdisable ; 
 int intrstatus ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_3__ roothub ; 
 int /*<<< orphan*/  u132_disable (struct u132*) ; 
 int u132_periodic_reinit (struct u132*) ; 
 int u132_read_pcimem (struct u132*,int,int*) ; 
 TYPE_2__* u132_to_hcd (struct u132*) ; 
 int u132_write_pcimem (struct u132*,int,int) ; 

__attribute__((used)) static int u132_run(struct u132 *u132)
{
	int retval;
	u32 control;
	u32 status;
	u32 fminterval;
	u32 periodicstart;
	u32 cmdstatus;
	u32 roothub_a;
	int mask = OHCI_INTR_INIT;
	int first = u132->hc_fminterval == 0;
	int sleep_time = 0;
	int reset_timeout = 30;	/* ... allow extra time */
	u132_disable(u132);
	if (first) {
		u32 temp;
		retval = u132_read_pcimem(u132, fminterval, &temp);
		if (retval)
			return retval;
		u132->hc_fminterval = temp & 0x3fff;
		u132->hc_fminterval |= FSMP(u132->hc_fminterval) << 16;
	}
	retval = u132_read_pcimem(u132, control, &u132->hc_control);
	if (retval)
		return retval;
	dev_info(&u132->platform_dev->dev, "resetting from state '%s', control "
		"= %08X\n", hcfs2string(u132->hc_control & OHCI_CTRL_HCFS),
		u132->hc_control);
	switch (u132->hc_control & OHCI_CTRL_HCFS) {
	case OHCI_USB_OPER:
		sleep_time = 0;
		break;
	case OHCI_USB_SUSPEND:
	case OHCI_USB_RESUME:
		u132->hc_control &= OHCI_CTRL_RWC;
		u132->hc_control |= OHCI_USB_RESUME;
		sleep_time = 10;
		break;
	default:
		u132->hc_control &= OHCI_CTRL_RWC;
		u132->hc_control |= OHCI_USB_RESET;
		sleep_time = 50;
		break;
	}
	retval = u132_write_pcimem(u132, control, u132->hc_control);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, control, &control);
	if (retval)
		return retval;
	msleep(sleep_time);
	retval = u132_read_pcimem(u132, roothub.a, &roothub_a);
	if (retval)
		return retval;
	if (!(roothub_a & RH_A_NPS)) {
		int temp;	/* power down each port */
		for (temp = 0; temp < u132->num_ports; temp++) {
			retval = u132_write_pcimem(u132,
				roothub.portstatus[temp], RH_PS_LSDA);
			if (retval)
				return retval;
		}
	}
	retval = u132_read_pcimem(u132, control, &control);
	if (retval)
		return retval;
retry:
	retval = u132_read_pcimem(u132, cmdstatus, &status);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, cmdstatus, OHCI_HCR);
	if (retval)
		return retval;
extra:	{
		retval = u132_read_pcimem(u132, cmdstatus, &status);
		if (retval)
			return retval;
		if (0 != (status & OHCI_HCR)) {
			if (--reset_timeout == 0) {
				dev_err(&u132->platform_dev->dev, "USB HC reset"
					" timed out!\n");
				return -ENODEV;
			} else {
				msleep(5);
				goto extra;
			}
		}
	}
	if (u132->flags & OHCI_QUIRK_INITRESET) {
		retval = u132_write_pcimem(u132, control, u132->hc_control);
		if (retval)
			return retval;
		retval = u132_read_pcimem(u132, control, &control);
		if (retval)
			return retval;
	}
	retval = u132_write_pcimem(u132, ed_controlhead, 0x00000000);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, ed_bulkhead, 0x11000000);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, hcca, 0x00000000);
	if (retval)
		return retval;
	retval = u132_periodic_reinit(u132);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, fminterval, &fminterval);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, periodicstart, &periodicstart);
	if (retval)
		return retval;
	if (0 == (fminterval & 0x3fff0000) || 0 == periodicstart) {
		if (!(u132->flags & OHCI_QUIRK_INITRESET)) {
			u132->flags |= OHCI_QUIRK_INITRESET;
			goto retry;
		} else
			dev_err(&u132->platform_dev->dev, "init err(%08x %04x)"
				"\n", fminterval, periodicstart);
	}			/* start controller operations */
	u132->hc_control &= OHCI_CTRL_RWC;
	u132->hc_control |= OHCI_CONTROL_INIT | OHCI_CTRL_BLE | OHCI_USB_OPER;
	retval = u132_write_pcimem(u132, control, u132->hc_control);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, cmdstatus, OHCI_BLF);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, cmdstatus, &cmdstatus);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, control, &control);
	if (retval)
		return retval;
	u132_to_hcd(u132)->state = HC_STATE_RUNNING;
	retval = u132_write_pcimem(u132, roothub.status, RH_HS_DRWE);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, intrstatus, mask);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, intrdisable,
		OHCI_INTR_MIE | OHCI_INTR_OC | OHCI_INTR_RHSC | OHCI_INTR_FNO |
		OHCI_INTR_UE | OHCI_INTR_RD | OHCI_INTR_SF | OHCI_INTR_WDH |
		OHCI_INTR_SO);
	if (retval)
		return retval;	/* handle root hub init quirks ... */
	retval = u132_read_pcimem(u132, roothub.a, &roothub_a);
	if (retval)
		return retval;
	roothub_a &= ~(RH_A_PSM | RH_A_OCPM);
	if (u132->flags & OHCI_QUIRK_SUPERIO) {
		roothub_a |= RH_A_NOCP;
		roothub_a &= ~(RH_A_POTPGT | RH_A_NPS);
		retval = u132_write_pcimem(u132, roothub.a, roothub_a);
		if (retval)
			return retval;
	} else if ((u132->flags & OHCI_QUIRK_AMD756) || distrust_firmware) {
		roothub_a |= RH_A_NPS;
		retval = u132_write_pcimem(u132, roothub.a, roothub_a);
		if (retval)
			return retval;
	}
	retval = u132_write_pcimem(u132, roothub.status, RH_HS_LPSC);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, roothub.b,
		(roothub_a & RH_A_NPS) ? 0 : RH_B_PPCM);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, control, &control);
	if (retval)
		return retval;
	mdelay((roothub_a >> 23) & 0x1fe);
	u132_to_hcd(u132)->state = HC_STATE_RUNNING;
	return 0;
}