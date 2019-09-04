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
struct TYPE_4__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  unqueue; } ;
struct lanai_vcc {TYPE_2__ tx; } ;
struct lanai_dev {int dummy; } ;
struct TYPE_3__ {int max_sdu; } ;
struct atm_qos {scalar_t__ aal; TYPE_1__ txtp; } ;

/* Variables and functions */
 int AAL0_TX_MULTIPLIER ; 
 int AAL5_TX_MULTIPLIER ; 
 scalar_t__ ATM_AAL0 ; 
 int ATM_CELL_SIZE ; 
 int lanai_get_sized_buffer (struct lanai_dev*,int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  vcc_tx_unqueue_aal0 ; 
 int /*<<< orphan*/  vcc_tx_unqueue_aal5 ; 

__attribute__((used)) static int lanai_setup_tx_vci(struct lanai_dev *lanai, struct lanai_vcc *lvcc,
	const struct atm_qos *qos)
{
	int max_sdu, multiplier;
	if (qos->aal == ATM_AAL0) {
		lvcc->tx.unqueue = vcc_tx_unqueue_aal0;
		max_sdu = ATM_CELL_SIZE - 1;
		multiplier = AAL0_TX_MULTIPLIER;
	} else {
		lvcc->tx.unqueue = vcc_tx_unqueue_aal5;
		max_sdu = qos->txtp.max_sdu;
		multiplier = AAL5_TX_MULTIPLIER;
	}
	return lanai_get_sized_buffer(lanai, &lvcc->tx.buf, max_sdu,
	    multiplier, "TX");
}