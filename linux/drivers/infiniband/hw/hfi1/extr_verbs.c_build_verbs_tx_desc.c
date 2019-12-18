#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ hdr_type; } ;
struct hfi1_sdma_header {int /*<<< orphan*/  pbc; TYPE_1__ hdr; } ;
struct verbs_txreq {int hdr_dwords; int /*<<< orphan*/  txreq; scalar_t__ ss; struct hfi1_sdma_header phdr; } ;
struct sdma_engine {TYPE_2__* dd; } ;
struct hfi1_ahg_info {int /*<<< orphan*/ * ahgdesc; int /*<<< orphan*/  ahgcount; int /*<<< orphan*/  ahgidx; int /*<<< orphan*/  tx_flags; } ;
typedef  int /*<<< orphan*/  pbc ;
struct TYPE_5__ {int /*<<< orphan*/  sdma_pad_phys; } ;

/* Variables and functions */
 int SIZE_OF_CRC ; 
 int SIZE_OF_LT ; 
 int build_verbs_ulp_payload (struct sdma_engine*,int,struct verbs_txreq*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hfi1_get_16b_padding (int,int) ; 
 int sdma_txadd_daddr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sdma_txadd_kvaddr (TYPE_2__*,int /*<<< orphan*/ *,struct hfi1_sdma_header*,int) ; 
 int sdma_txinit_ahg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbs_sdma_complete ; 

__attribute__((used)) static int build_verbs_tx_desc(
	struct sdma_engine *sde,
	u32 length,
	struct verbs_txreq *tx,
	struct hfi1_ahg_info *ahg_info,
	u64 pbc)
{
	int ret = 0;
	struct hfi1_sdma_header *phdr = &tx->phdr;
	u16 hdrbytes = (tx->hdr_dwords + sizeof(pbc) / 4) << 2;
	u8 extra_bytes = 0;

	if (tx->phdr.hdr.hdr_type) {
		/*
		 * hdrbytes accounts for PBC. Need to subtract 8 bytes
		 * before calculating padding.
		 */
		extra_bytes = hfi1_get_16b_padding(hdrbytes - 8, length) +
			      (SIZE_OF_CRC << 2) + SIZE_OF_LT;
	}
	if (!ahg_info->ahgcount) {
		ret = sdma_txinit_ahg(
			&tx->txreq,
			ahg_info->tx_flags,
			hdrbytes + length +
			extra_bytes,
			ahg_info->ahgidx,
			0,
			NULL,
			0,
			verbs_sdma_complete);
		if (ret)
			goto bail_txadd;
		phdr->pbc = cpu_to_le64(pbc);
		ret = sdma_txadd_kvaddr(
			sde->dd,
			&tx->txreq,
			phdr,
			hdrbytes);
		if (ret)
			goto bail_txadd;
	} else {
		ret = sdma_txinit_ahg(
			&tx->txreq,
			ahg_info->tx_flags,
			length,
			ahg_info->ahgidx,
			ahg_info->ahgcount,
			ahg_info->ahgdesc,
			hdrbytes,
			verbs_sdma_complete);
		if (ret)
			goto bail_txadd;
	}
	/* add the ulp payload - if any. tx->ss can be NULL for acks */
	if (tx->ss) {
		ret = build_verbs_ulp_payload(sde, length, tx);
		if (ret)
			goto bail_txadd;
	}

	/* add icrc, lt byte, and padding to flit */
	if (extra_bytes)
		ret = sdma_txadd_daddr(sde->dd, &tx->txreq,
				       sde->dd->sdma_pad_phys, extra_bytes);

bail_txadd:
	return ret;
}