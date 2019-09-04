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
typedef  unsigned long u64 ;
typedef  unsigned int u32 ;
struct user_sdma_txreq {int /*<<< orphan*/  txreq; } ;
struct TYPE_4__ {unsigned long fragsize; } ;
struct user_sdma_request {int iov_idx; int data_iovs; struct user_sdma_iovec* iovs; TYPE_2__ info; struct hfi1_user_sdma_pkt_q* pq; } ;
struct TYPE_3__ {scalar_t__ iov_base; } ;
struct user_sdma_iovec {unsigned long offset; unsigned int npages; int /*<<< orphan*/ * pages; TYPE_1__ iov; } ;
struct hfi1_user_sdma_pkt_q {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  SDMA_DBG (struct user_sdma_request*,char*,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned long offset_in_page (unsigned long) ; 
 int sdma_txadd_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int user_sdma_txadd(struct user_sdma_request *req,
			   struct user_sdma_txreq *tx,
			   struct user_sdma_iovec *iovec, u32 datalen,
			   u32 *queued_ptr, u32 *data_sent_ptr,
			   u64 *iov_offset_ptr)
{
	int ret;
	unsigned int pageidx, len;
	unsigned long base, offset;
	u64 iov_offset = *iov_offset_ptr;
	u32 queued = *queued_ptr, data_sent = *data_sent_ptr;
	struct hfi1_user_sdma_pkt_q *pq = req->pq;

	base = (unsigned long)iovec->iov.iov_base;
	offset = offset_in_page(base + iovec->offset + iov_offset);
	pageidx = (((iovec->offset + iov_offset + base) - (base & PAGE_MASK)) >>
		   PAGE_SHIFT);
	len = offset + req->info.fragsize > PAGE_SIZE ?
		PAGE_SIZE - offset : req->info.fragsize;
	len = min((datalen - queued), len);
	ret = sdma_txadd_page(pq->dd, &tx->txreq, iovec->pages[pageidx],
			      offset, len);
	if (ret) {
		SDMA_DBG(req, "SDMA txreq add page failed %d\n", ret);
		return ret;
	}
	iov_offset += len;
	queued += len;
	data_sent += len;
	if (unlikely(queued < datalen && pageidx == iovec->npages &&
		     req->iov_idx < req->data_iovs - 1)) {
		iovec->offset += iov_offset;
		iovec = &req->iovs[++req->iov_idx];
		iov_offset = 0;
	}

	*queued_ptr = queued;
	*data_sent_ptr = data_sent;
	*iov_offset_ptr = iov_offset;
	return ret;
}