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
typedef  int u32 ;
struct TYPE_2__ {int idx_clr_mask; } ;
struct cxgbi_ppm {TYPE_1__ tformat; } ;
struct cxgbi_pagepod_hdr {void* page_offset; void* max_offset; void* pgsz_tag_clr; scalar_t__ rsvd; void* vld_tid; } ;

/* Variables and functions */
 unsigned int PPOD_TID (unsigned int) ; 
 unsigned int PPOD_VALID_FLAG ; 
 void* htonl (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int,unsigned int,unsigned int) ; 

void cxgbi_ppm_make_ppod_hdr(struct cxgbi_ppm *ppm, u32 tag,
			     unsigned int tid, unsigned int offset,
			     unsigned int length,
			     struct cxgbi_pagepod_hdr *hdr)
{
	/* The ddp tag in pagepod should be with bit 31:30 set to 0.
	 * The ddp Tag on the wire should be with non-zero 31:30 to the peer
	 */
	tag &= 0x3FFFFFFF;

	hdr->vld_tid = htonl(PPOD_VALID_FLAG | PPOD_TID(tid));

	hdr->rsvd = 0;
	hdr->pgsz_tag_clr = htonl(tag & ppm->tformat.idx_clr_mask);
	hdr->max_offset = htonl(length);
	hdr->page_offset = htonl(offset);

	pr_debug("ippm: tag 0x%x, tid 0x%x, xfer %u, off %u.\n",
		 tag, tid, length, offset);
}