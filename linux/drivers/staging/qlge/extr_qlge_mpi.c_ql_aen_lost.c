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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;
struct mbox_params {int out_count; int /*<<< orphan*/ * mbox_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ql_get_mb_sts (struct ql_adapter*,struct mbox_params*) ; 

__attribute__((used)) static int ql_aen_lost(struct ql_adapter *qdev, struct mbox_params *mbcp)
{
	int status;

	mbcp->out_count = 6;

	status = ql_get_mb_sts(qdev, mbcp);
	if (status)
		netif_err(qdev, drv, qdev->ndev, "Lost AEN broken!\n");
	else {
		int i;
		netif_err(qdev, drv, qdev->ndev, "Lost AEN detected.\n");
		for (i = 0; i < mbcp->out_count; i++)
			netif_err(qdev, drv, qdev->ndev, "mbox_out[%d] = 0x%.08x.\n",
				  i, mbcp->mbox_out[i]);

	}

	return status;
}