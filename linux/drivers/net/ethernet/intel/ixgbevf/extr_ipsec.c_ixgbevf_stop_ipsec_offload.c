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
struct ixgbevf_ipsec {struct ixgbevf_ipsec* tx_tbl; struct ixgbevf_ipsec* rx_tbl; } ;
struct ixgbevf_adapter {struct ixgbevf_ipsec* ipsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ixgbevf_ipsec*) ; 

void ixgbevf_stop_ipsec_offload(struct ixgbevf_adapter *adapter)
{
	struct ixgbevf_ipsec *ipsec = adapter->ipsec;

	adapter->ipsec = NULL;
	if (ipsec) {
		kfree(ipsec->rx_tbl);
		kfree(ipsec->tx_tbl);
		kfree(ipsec);
	}
}