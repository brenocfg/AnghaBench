#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/ * pbc; } ;
struct user_sdma_txreq {int /*<<< orphan*/  txreq; TYPE_1__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pbc; } ;
struct user_sdma_request {int /*<<< orphan*/  ahg_idx; TYPE_3__ hdr; struct hfi1_user_sdma_pkt_q* pq; } ;
struct hfi1_user_sdma_pkt_q {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int LRH2PBC (scalar_t__) ; 
 scalar_t__ PBC2LRH (int) ; 
 int /*<<< orphan*/  SDMA_TXREQ_F_AHG_COPY ; 
 int check_header_template (struct user_sdma_request*,TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ get_lrh_len (TYPE_3__,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pad_len (scalar_t__) ; 
 int sdma_txadd_kvaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  sdma_txclean (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sdma_txinit_ahg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_sdma_txreq_cb ; 

__attribute__((used)) static int user_sdma_txadd_ahg(struct user_sdma_request *req,
			       struct user_sdma_txreq *tx,
			       u32 datalen)
{
	int ret;
	u16 pbclen = le16_to_cpu(req->hdr.pbc[0]);
	u32 lrhlen = get_lrh_len(req->hdr, pad_len(datalen));
	struct hfi1_user_sdma_pkt_q *pq = req->pq;

	/*
	 * Copy the request header into the tx header
	 * because the HW needs a cacheline-aligned
	 * address.
	 * This copy can be optimized out if the hdr
	 * member of user_sdma_request were also
	 * cacheline aligned.
	 */
	memcpy(&tx->hdr, &req->hdr, sizeof(tx->hdr));
	if (PBC2LRH(pbclen) != lrhlen) {
		pbclen = (pbclen & 0xf000) | LRH2PBC(lrhlen);
		tx->hdr.pbc[0] = cpu_to_le16(pbclen);
	}
	ret = check_header_template(req, &tx->hdr, lrhlen, datalen);
	if (ret)
		return ret;
	ret = sdma_txinit_ahg(&tx->txreq, SDMA_TXREQ_F_AHG_COPY,
			      sizeof(tx->hdr) + datalen, req->ahg_idx,
			      0, NULL, 0, user_sdma_txreq_cb);
	if (ret)
		return ret;
	ret = sdma_txadd_kvaddr(pq->dd, &tx->txreq, &tx->hdr, sizeof(tx->hdr));
	if (ret)
		sdma_txclean(pq->dd, &tx->txreq);
	return ret;
}