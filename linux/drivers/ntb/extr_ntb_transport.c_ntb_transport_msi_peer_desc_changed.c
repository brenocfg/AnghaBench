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
struct ntb_transport_ctx {int qp_count; TYPE_2__* ndev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ntb_transport_setup_qp_peer_msi (struct ntb_transport_ctx*,int) ; 

__attribute__((used)) static void ntb_transport_msi_peer_desc_changed(struct ntb_transport_ctx *nt)
{
	int i;

	dev_dbg(&nt->ndev->pdev->dev, "Peer MSI descriptors changed");

	for (i = 0; i < nt->qp_count; i++)
		ntb_transport_setup_qp_peer_msi(nt, i);
}