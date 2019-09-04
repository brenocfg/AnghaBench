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
typedef  scalar_t__ u16 ;
struct cnic_local {scalar_t__* rx_cons_ptr; scalar_t__* tx_cons_ptr; scalar_t__ tx_cons; scalar_t__ rx_cons; int /*<<< orphan*/  cnic_local_flags; TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnic_uinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_LCL_FL_L2_WAIT ; 
 int /*<<< orphan*/  CNIC_LCL_FL_RINGS_INITED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cnic_l2_completion (struct cnic_local*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_event_notify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_chk_pkt_rings(struct cnic_local *cp)
{
	u16 rx_cons, tx_cons;
	int comp = 0;

	if (!test_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags))
		return;

	rx_cons = *cp->rx_cons_ptr;
	tx_cons = *cp->tx_cons_ptr;
	if (cp->tx_cons != tx_cons || cp->rx_cons != rx_cons) {
		if (test_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags))
			comp = cnic_l2_completion(cp);

		cp->tx_cons = tx_cons;
		cp->rx_cons = rx_cons;

		if (cp->udev)
			uio_event_notify(&cp->udev->cnic_uinfo);
	}
	if (comp)
		clear_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags);
}