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
typedef  int /*<<< orphan*/  u32 ;
struct qib_pportdata {int port; TYPE_1__* cpspec; struct qib_devdata* dd; } ;
struct qib_devdata {TYPE_2__* cspec; } ;
struct TYPE_4__ {int recovery_ports_initted; int /*<<< orphan*/  r1; } ;
struct TYPE_3__ {int recovery_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  BISTEN_AT ; 
 int /*<<< orphan*/  BISTEN_ETM ; 
 int /*<<< orphan*/  BISTEN_PORT_SEL ; 
 int /*<<< orphan*/  LEN_AT ; 
 int /*<<< orphan*/  LEN_ETM ; 
 int /*<<< orphan*/  LEN_PORT_SEL ; 
 int /*<<< orphan*/ * at ; 
 int /*<<< orphan*/ * atetm_1port ; 
 int /*<<< orphan*/ * atetm_2port ; 
 int /*<<< orphan*/ * portsel_2port ; 
 int /*<<< orphan*/ * portsel_port1 ; 
 int /*<<< orphan*/ * portsel_port2 ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 scalar_t__ qib_r_grab (struct qib_devdata*) ; 
 scalar_t__ qib_r_shift (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qib_r_update (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reset_at ; 
 int /*<<< orphan*/ * reset_atetm ; 

__attribute__((used)) static void setup_7322_link_recovery(struct qib_pportdata *ppd, u32 both)
{
	u8 *portsel, *etm;
	struct qib_devdata *dd = ppd->dd;

	if (!ppd->dd->cspec->r1)
		return;
	if (!both) {
		dd->cspec->recovery_ports_initted++;
		ppd->cpspec->recovery_init = 1;
	}
	if (!both && dd->cspec->recovery_ports_initted == 1) {
		portsel = ppd->port == 1 ? portsel_port1 : portsel_port2;
		etm = atetm_1port;
	} else {
		portsel = portsel_2port;
		etm = atetm_2port;
	}

	if (qib_r_grab(dd) < 0 ||
		qib_r_shift(dd, BISTEN_ETM, LEN_ETM, reset_atetm, NULL) < 0 ||
		qib_r_update(dd, BISTEN_ETM) < 0 ||
		qib_r_shift(dd, BISTEN_AT, LEN_AT, reset_at, NULL) < 0 ||
		qib_r_update(dd, BISTEN_AT) < 0 ||
		qib_r_shift(dd, BISTEN_PORT_SEL, LEN_PORT_SEL,
			    portsel, NULL) < 0 ||
		qib_r_update(dd, BISTEN_PORT_SEL) < 0 ||
		qib_r_shift(dd, BISTEN_AT, LEN_AT, at, NULL) < 0 ||
		qib_r_update(dd, BISTEN_AT) < 0 ||
		qib_r_shift(dd, BISTEN_ETM, LEN_ETM, etm, NULL) < 0 ||
		qib_r_update(dd, BISTEN_ETM) < 0)
		qib_dev_err(dd, "Failed IB link recovery setup\n");
}