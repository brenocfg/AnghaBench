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
struct nci_mode_set_cmd {scalar_t__ mode; int /*<<< orphan*/  cmd_type; } ;
struct llt_ndlc {int /*<<< orphan*/  phy_id; TYPE_1__* ops; scalar_t__ powered; int /*<<< orphan*/  ndev; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ST_NCI_CORE_PROP ; 
 int /*<<< orphan*/  ST_NCI_SET_NFC_MODE ; 
 int /*<<< orphan*/  nci_prop_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void ndlc_close(struct llt_ndlc *ndlc)
{
	struct nci_mode_set_cmd cmd;

	cmd.cmd_type = ST_NCI_SET_NFC_MODE;
	cmd.mode = 0;

	/* toggle reset pin */
	ndlc->ops->enable(ndlc->phy_id);

	nci_prop_cmd(ndlc->ndev, ST_NCI_CORE_PROP,
		     sizeof(struct nci_mode_set_cmd), (__u8 *)&cmd);

	ndlc->powered = 0;
	ndlc->ops->disable(ndlc->phy_id);
}