#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vci_t ;
struct TYPE_8__ {struct atm_vcc const* atmvcc; } ;
struct TYPE_5__ {struct atm_vcc const* atmvcc; } ;
struct lanai_vcc {TYPE_4__ rx; TYPE_1__ tx; } ;
struct lanai_dev {scalar_t__ naal0; int /*<<< orphan*/  conf2; struct lanai_vcc** vccs; struct atm_vcc const* cbrvcc; } ;
struct TYPE_7__ {scalar_t__ traffic_class; } ;
struct TYPE_6__ {scalar_t__ traffic_class; } ;
struct atm_qos {scalar_t__ aal; TYPE_3__ rxtp; TYPE_2__ txtp; } ;
struct atm_vcc {struct atm_qos qos; } ;

/* Variables and functions */
 scalar_t__ ATM_AAL0 ; 
 scalar_t__ ATM_CBR ; 
 scalar_t__ ATM_NONE ; 
 int /*<<< orphan*/  CONFIG2_VCI0_NORMAL ; 
 int /*<<< orphan*/  conf2_write_if_powerup (struct lanai_dev*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vci0_is_ok (struct lanai_dev*,struct atm_qos const*) ; 

__attribute__((used)) static int vci_is_ok(struct lanai_dev *lanai, vci_t vci,
	const struct atm_vcc *atmvcc)
{
	const struct atm_qos *qos = &atmvcc->qos;
	const struct lanai_vcc *lvcc = lanai->vccs[vci];
	if (vci == 0 && !vci0_is_ok(lanai, qos))
		return 0;
	if (unlikely(lvcc != NULL)) {
		if (qos->rxtp.traffic_class != ATM_NONE &&
		    lvcc->rx.atmvcc != NULL && lvcc->rx.atmvcc != atmvcc)
			return 0;
		if (qos->txtp.traffic_class != ATM_NONE &&
		    lvcc->tx.atmvcc != NULL && lvcc->tx.atmvcc != atmvcc)
			return 0;
		if (qos->txtp.traffic_class == ATM_CBR &&
		    lanai->cbrvcc != NULL && lanai->cbrvcc != atmvcc)
			return 0;
	}
	if (qos->aal == ATM_AAL0 && lanai->naal0 == 0 &&
	    qos->rxtp.traffic_class != ATM_NONE) {
		const struct lanai_vcc *vci0 = lanai->vccs[0];
		if (vci0 != NULL && vci0->rx.atmvcc != NULL)
			return 0;
		lanai->conf2 &= ~CONFIG2_VCI0_NORMAL;
		conf2_write_if_powerup(lanai);
	}
	return 1;
}