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
struct ucc_geth_private {TYPE_2__* ug_info; struct ucc_fast_private* uccf; } ;
struct ucc_fast_private {int enabled_tx; int enabled_rx; scalar_t__ stopped_rx; scalar_t__ stopped_tx; } ;
typedef  enum comm_dir { ____Placeholder_comm_dir } comm_dir ;
struct TYPE_3__ {scalar_t__ ucc_num; } ;
struct TYPE_4__ {TYPE_1__ uf_info; } ;

/* Variables and functions */
 int COMM_DIR_RX ; 
 int COMM_DIR_TX ; 
 int EINVAL ; 
 scalar_t__ UCC_MAX_NUM ; 
 scalar_t__ netif_msg_probe (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  ucc_fast_enable (struct ucc_fast_private*,int) ; 
 int /*<<< orphan*/  ugeth_restart_rx (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  ugeth_restart_tx (struct ucc_geth_private*) ; 

__attribute__((used)) static int ugeth_enable(struct ucc_geth_private *ugeth, enum comm_dir mode)
{
	struct ucc_fast_private *uccf;
	int enabled_tx, enabled_rx;

	uccf = ugeth->uccf;

	/* check if the UCC number is in range. */
	if (ugeth->ug_info->uf_info.ucc_num >= UCC_MAX_NUM) {
		if (netif_msg_probe(ugeth))
			pr_err("ucc_num out of range\n");
		return -EINVAL;
	}

	enabled_tx = uccf->enabled_tx;
	enabled_rx = uccf->enabled_rx;

	/* Get Tx and Rx going again, in case this channel was actively
	disabled. */
	if ((mode & COMM_DIR_TX) && (!enabled_tx) && uccf->stopped_tx)
		ugeth_restart_tx(ugeth);
	if ((mode & COMM_DIR_RX) && (!enabled_rx) && uccf->stopped_rx)
		ugeth_restart_rx(ugeth);

	ucc_fast_enable(uccf, mode);	/* OK to do even if not disabled */

	return 0;

}