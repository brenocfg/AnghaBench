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
struct TYPE_5__ {int tcr; } ;
struct TYPE_4__ {scalar_t__ owner; unsigned char tsr0; unsigned char tsr1; } ;
struct vnt_tx_desc {TYPE_3__* td_info; TYPE_2__ td1; TYPE_1__ td0; struct vnt_tx_desc* next; } ;
struct vnt_private {scalar_t__* iTDUsed; struct vnt_tx_desc** apTailTD; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 scalar_t__ OWNED_BY_NIC ; 
 int TCR_STP ; 
 int TD_FLAGS_NETIF_SKB ; 
 int TD_FLAGS_PRIV_SKB ; 
 unsigned char TSR1_TERR ; 
 int /*<<< orphan*/  device_free_tx_buf (struct vnt_private*,struct vnt_tx_desc*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  vnt_int_report_rate (struct vnt_private*,TYPE_3__*,unsigned char,unsigned char) ; 

__attribute__((used)) static int device_tx_srv(struct vnt_private *priv, unsigned int idx)
{
	struct vnt_tx_desc *desc;
	int                      works = 0;
	unsigned char byTsr0;
	unsigned char byTsr1;

	for (desc = priv->apTailTD[idx]; priv->iTDUsed[idx] > 0; desc = desc->next) {
		if (desc->td0.owner == OWNED_BY_NIC)
			break;
		if (works++ > 15)
			break;

		byTsr0 = desc->td0.tsr0;
		byTsr1 = desc->td0.tsr1;

		/* Only the status of first TD in the chain is correct */
		if (desc->td1.tcr & TCR_STP) {
			if ((desc->td_info->flags & TD_FLAGS_NETIF_SKB) != 0) {
				if (!(byTsr1 & TSR1_TERR)) {
					if (byTsr0 != 0) {
						pr_debug(" Tx[%d] OK but has error. tsr1[%02X] tsr0[%02X]\n",
							 (int)idx, byTsr1,
							 byTsr0);
					}
				} else {
					pr_debug(" Tx[%d] dropped & tsr1[%02X] tsr0[%02X]\n",
						 (int)idx, byTsr1, byTsr0);
				}
			}

			if (byTsr1 & TSR1_TERR) {
				if ((desc->td_info->flags & TD_FLAGS_PRIV_SKB) != 0) {
					pr_debug(" Tx[%d] fail has error. tsr1[%02X] tsr0[%02X]\n",
						 (int)idx, byTsr1, byTsr0);
				}
			}

			vnt_int_report_rate(priv, desc->td_info, byTsr0, byTsr1);

			device_free_tx_buf(priv, desc);
			priv->iTDUsed[idx]--;
		}
	}

	priv->apTailTD[idx] = desc;

	return works;
}