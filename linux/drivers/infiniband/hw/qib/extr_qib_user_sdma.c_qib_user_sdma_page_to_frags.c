#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union qib_seqnum {int val; int /*<<< orphan*/  pkt; int /*<<< orphan*/  seq; } ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct qib_user_sdma_queue {int dummy; } ;
struct qib_user_sdma_pkt {size_t tidsmidx; int payload_size; scalar_t__ frag_size; scalar_t__ bytes_togo; size_t naddr; size_t addrlimit; size_t index; size_t tidsmcount; scalar_t__ tiddma; TYPE_2__* tidsm; TYPE_1__* addr; } ;
struct TYPE_7__ {void* pkt_flags; void* chksum; int /*<<< orphan*/  ver_ctxt_tid_offset; } ;
struct qib_message_header {int flags; int* uwords; void** bth; TYPE_3__ iph; void** lrh; } ;
struct qib_devdata {TYPE_4__* pcidev; } ;
struct page {int dummy; } ;
typedef  void* dma_addr_t ;
typedef  void* __le16 ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ length; int offset; int tid; } ;
struct TYPE_5__ {int dma_mapped; scalar_t__ length; void* addr; int /*<<< orphan*/  dma_length; scalar_t__ kvaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int ENOMEM ; 
 int QIB_LRH_BTH ; 
 int QLOGIC_IB_I_TID_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int be16_to_cpu (void*) ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 void* dma_map_page (int /*<<< orphan*/ *,struct page*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 void* dma_map_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int le16_to_cpu (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void**,scalar_t__) ; 
 int /*<<< orphan*/  put_user_page (struct page*) ; 
 void* qib_user_sdma_alloc_header (struct qib_user_sdma_queue*,scalar_t__,void**) ; 
 int /*<<< orphan*/  qib_user_sdma_init_frag (struct qib_user_sdma_pkt*,size_t,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__,scalar_t__,struct page*,void*,void*,scalar_t__) ; 

__attribute__((used)) static int qib_user_sdma_page_to_frags(const struct qib_devdata *dd,
				       struct qib_user_sdma_queue *pq,
				       struct qib_user_sdma_pkt *pkt,
				       struct page *page, u16 put,
				       u16 offset, u16 len, void *kvaddr)
{
	__le16 *pbc16;
	void *pbcvaddr;
	struct qib_message_header *hdr;
	u16 newlen, pbclen, lastdesc, dma_mapped;
	u32 vcto;
	union qib_seqnum seqnum;
	dma_addr_t pbcdaddr;
	dma_addr_t dma_addr =
		dma_map_page(&dd->pcidev->dev,
			page, offset, len, DMA_TO_DEVICE);
	int ret = 0;

	if (dma_mapping_error(&dd->pcidev->dev, dma_addr)) {
		/*
		 * dma mapping error, pkt has not managed
		 * this page yet, return the page here so
		 * the caller can ignore this page.
		 */
		if (put) {
			put_user_page(page);
		} else {
			/* coalesce case */
			kunmap(page);
			__free_page(page);
		}
		ret = -ENOMEM;
		goto done;
	}
	offset = 0;
	dma_mapped = 1;


next_fragment:

	/*
	 * In tid-sdma, the transfer length is restricted by
	 * receiver side current tid page length.
	 */
	if (pkt->tiddma && len > pkt->tidsm[pkt->tidsmidx].length)
		newlen = pkt->tidsm[pkt->tidsmidx].length;
	else
		newlen = len;

	/*
	 * Then the transfer length is restricted by MTU.
	 * the last descriptor flag is determined by:
	 * 1. the current packet is at frag size length.
	 * 2. the current tid page is done if tid-sdma.
	 * 3. there is no more byte togo if sdma.
	 */
	lastdesc = 0;
	if ((pkt->payload_size + newlen) >= pkt->frag_size) {
		newlen = pkt->frag_size - pkt->payload_size;
		lastdesc = 1;
	} else if (pkt->tiddma) {
		if (newlen == pkt->tidsm[pkt->tidsmidx].length)
			lastdesc = 1;
	} else {
		if (newlen == pkt->bytes_togo)
			lastdesc = 1;
	}

	/* fill the next fragment in this page */
	qib_user_sdma_init_frag(pkt, pkt->naddr, /* index */
		offset, newlen,		/* offset, len */
		0, lastdesc,		/* first last desc */
		put, dma_mapped,	/* put page, dma mapped */
		page, kvaddr,		/* struct page, virt addr */
		dma_addr, len);		/* dma addr, dma length */
	pkt->bytes_togo -= newlen;
	pkt->payload_size += newlen;
	pkt->naddr++;
	if (pkt->naddr == pkt->addrlimit) {
		ret = -EFAULT;
		goto done;
	}

	/* If there is no more byte togo. (lastdesc==1) */
	if (pkt->bytes_togo == 0) {
		/* The packet is done, header is not dma mapped yet.
		 * it should be from kmalloc */
		if (!pkt->addr[pkt->index].addr) {
			pkt->addr[pkt->index].addr =
				dma_map_single(&dd->pcidev->dev,
					pkt->addr[pkt->index].kvaddr,
					pkt->addr[pkt->index].dma_length,
					DMA_TO_DEVICE);
			if (dma_mapping_error(&dd->pcidev->dev,
					pkt->addr[pkt->index].addr)) {
				ret = -ENOMEM;
				goto done;
			}
			pkt->addr[pkt->index].dma_mapped = 1;
		}

		goto done;
	}

	/* If tid-sdma, advance tid info. */
	if (pkt->tiddma) {
		pkt->tidsm[pkt->tidsmidx].length -= newlen;
		if (pkt->tidsm[pkt->tidsmidx].length) {
			pkt->tidsm[pkt->tidsmidx].offset += newlen;
		} else {
			pkt->tidsmidx++;
			if (pkt->tidsmidx == pkt->tidsmcount) {
				ret = -EFAULT;
				goto done;
			}
		}
	}

	/*
	 * If this is NOT the last descriptor. (newlen==len)
	 * the current packet is not done yet, but the current
	 * send side page is done.
	 */
	if (lastdesc == 0)
		goto done;

	/*
	 * If running this driver under PSM with message size
	 * fitting into one transfer unit, it is not possible
	 * to pass this line. otherwise, it is a buggggg.
	 */

	/*
	 * Since the current packet is done, and there are more
	 * bytes togo, we need to create a new sdma header, copying
	 * from previous sdma header and modify both.
	 */
	pbclen = pkt->addr[pkt->index].length;
	pbcvaddr = qib_user_sdma_alloc_header(pq, pbclen, &pbcdaddr);
	if (!pbcvaddr) {
		ret = -ENOMEM;
		goto done;
	}
	/* Copy the previous sdma header to new sdma header */
	pbc16 = (__le16 *)pkt->addr[pkt->index].kvaddr;
	memcpy(pbcvaddr, pbc16, pbclen);

	/* Modify the previous sdma header */
	hdr = (struct qib_message_header *)&pbc16[4];

	/* New pbc length */
	pbc16[0] = cpu_to_le16(le16_to_cpu(pbc16[0])-(pkt->bytes_togo>>2));

	/* New packet length */
	hdr->lrh[2] = cpu_to_be16(le16_to_cpu(pbc16[0]));

	if (pkt->tiddma) {
		/* turn on the header suppression */
		hdr->iph.pkt_flags =
			cpu_to_le16(le16_to_cpu(hdr->iph.pkt_flags)|0x2);
		/* turn off ACK_REQ: 0x04 and EXPECTED_DONE: 0x20 */
		hdr->flags &= ~(0x04|0x20);
	} else {
		/* turn off extra bytes: 20-21 bits */
		hdr->bth[0] = cpu_to_be32(be32_to_cpu(hdr->bth[0])&0xFFCFFFFF);
		/* turn off ACK_REQ: 0x04 */
		hdr->flags &= ~(0x04);
	}

	/* New kdeth checksum */
	vcto = le32_to_cpu(hdr->iph.ver_ctxt_tid_offset);
	hdr->iph.chksum = cpu_to_le16(QIB_LRH_BTH +
		be16_to_cpu(hdr->lrh[2]) -
		((vcto>>16)&0xFFFF) - (vcto&0xFFFF) -
		le16_to_cpu(hdr->iph.pkt_flags));

	/* The packet is done, header is not dma mapped yet.
	 * it should be from kmalloc */
	if (!pkt->addr[pkt->index].addr) {
		pkt->addr[pkt->index].addr =
			dma_map_single(&dd->pcidev->dev,
				pkt->addr[pkt->index].kvaddr,
				pkt->addr[pkt->index].dma_length,
				DMA_TO_DEVICE);
		if (dma_mapping_error(&dd->pcidev->dev,
				pkt->addr[pkt->index].addr)) {
			ret = -ENOMEM;
			goto done;
		}
		pkt->addr[pkt->index].dma_mapped = 1;
	}

	/* Modify the new sdma header */
	pbc16 = (__le16 *)pbcvaddr;
	hdr = (struct qib_message_header *)&pbc16[4];

	/* New pbc length */
	pbc16[0] = cpu_to_le16(le16_to_cpu(pbc16[0])-(pkt->payload_size>>2));

	/* New packet length */
	hdr->lrh[2] = cpu_to_be16(le16_to_cpu(pbc16[0]));

	if (pkt->tiddma) {
		/* Set new tid and offset for new sdma header */
		hdr->iph.ver_ctxt_tid_offset = cpu_to_le32(
			(le32_to_cpu(hdr->iph.ver_ctxt_tid_offset)&0xFF000000) +
			(pkt->tidsm[pkt->tidsmidx].tid<<QLOGIC_IB_I_TID_SHIFT) +
			(pkt->tidsm[pkt->tidsmidx].offset>>2));
	} else {
		/* Middle protocol new packet offset */
		hdr->uwords[2] += pkt->payload_size;
	}

	/* New kdeth checksum */
	vcto = le32_to_cpu(hdr->iph.ver_ctxt_tid_offset);
	hdr->iph.chksum = cpu_to_le16(QIB_LRH_BTH +
		be16_to_cpu(hdr->lrh[2]) -
		((vcto>>16)&0xFFFF) - (vcto&0xFFFF) -
		le16_to_cpu(hdr->iph.pkt_flags));

	/* Next sequence number in new sdma header */
	seqnum.val = be32_to_cpu(hdr->bth[2]);
	if (pkt->tiddma)
		seqnum.seq++;
	else
		seqnum.pkt++;
	hdr->bth[2] = cpu_to_be32(seqnum.val);

	/* Init new sdma header. */
	qib_user_sdma_init_frag(pkt, pkt->naddr, /* index */
		0, pbclen,		/* offset, len */
		1, 0,			/* first last desc */
		0, 0,			/* put page, dma mapped */
		NULL, pbcvaddr,		/* struct page, virt addr */
		pbcdaddr, pbclen);	/* dma addr, dma length */
	pkt->index = pkt->naddr;
	pkt->payload_size = 0;
	pkt->naddr++;
	if (pkt->naddr == pkt->addrlimit) {
		ret = -EFAULT;
		goto done;
	}

	/* Prepare for next fragment in this page */
	if (newlen != len) {
		if (dma_mapped) {
			put = 0;
			dma_mapped = 0;
			page = NULL;
			kvaddr = NULL;
		}
		len -= newlen;
		offset += newlen;

		goto next_fragment;
	}

done:
	return ret;
}