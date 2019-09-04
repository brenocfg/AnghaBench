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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct vnic_txreq {int plen; int /*<<< orphan*/  pbc_val; int /*<<< orphan*/  txreq; TYPE_1__* skb; } ;
struct sdma_engine {int /*<<< orphan*/  dd; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int build_vnic_ulp_payload (struct sdma_engine*,struct vnic_txreq*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int sdma_txadd_kvaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sdma_txinit_ahg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vnic_sdma_complete ; 

__attribute__((used)) static int build_vnic_tx_desc(struct sdma_engine *sde,
			      struct vnic_txreq *tx,
			      u64 pbc)
{
	int ret = 0;
	u16 hdrbytes = 2 << 2;  /* PBC */

	ret = sdma_txinit_ahg(
		&tx->txreq,
		0,
		hdrbytes + tx->skb->len + tx->plen,
		0,
		0,
		NULL,
		0,
		vnic_sdma_complete);
	if (unlikely(ret))
		goto bail_txadd;

	/* add pbc */
	tx->pbc_val = cpu_to_le64(pbc);
	ret = sdma_txadd_kvaddr(
		sde->dd,
		&tx->txreq,
		&tx->pbc_val,
		hdrbytes);
	if (unlikely(ret))
		goto bail_txadd;

	/* add the ulp payload */
	ret = build_vnic_ulp_payload(sde, tx);
bail_txadd:
	return ret;
}