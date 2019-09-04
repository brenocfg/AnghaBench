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
struct ucc_geth_private {struct ucc_fast_private* uccf; TYPE_2__* ug_info; } ;
struct ucc_fast_private {int /*<<< orphan*/  stopped_rx; scalar_t__ enabled_rx; int /*<<< orphan*/  stopped_tx; scalar_t__ enabled_tx; } ;
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
 int /*<<< orphan*/  ucc_fast_disable (struct ucc_fast_private*,int) ; 
 int /*<<< orphan*/  ugeth_graceful_stop_rx (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  ugeth_graceful_stop_tx (struct ucc_geth_private*) ; 

__attribute__((used)) static int ugeth_disable(struct ucc_geth_private *ugeth, enum comm_dir mode)
{
	struct ucc_fast_private *uccf;

	uccf = ugeth->uccf;

	/* check if the UCC number is in range. */
	if (ugeth->ug_info->uf_info.ucc_num >= UCC_MAX_NUM) {
		if (netif_msg_probe(ugeth))
			pr_err("ucc_num out of range\n");
		return -EINVAL;
	}

	/* Stop any transmissions */
	if ((mode & COMM_DIR_TX) && uccf->enabled_tx && !uccf->stopped_tx)
		ugeth_graceful_stop_tx(ugeth);

	/* Stop any receptions */
	if ((mode & COMM_DIR_RX) && uccf->enabled_rx && !uccf->stopped_rx)
		ugeth_graceful_stop_rx(ugeth);

	ucc_fast_disable(ugeth->uccf, mode); /* OK to do even if not enabled */

	return 0;
}