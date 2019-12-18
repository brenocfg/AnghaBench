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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sdma_txreq {void (* complete ) (struct sdma_txreq*,int) ;TYPE_1__* descs; scalar_t__ packet_len; scalar_t__ tlen; int /*<<< orphan*/ * wait; int /*<<< orphan*/ * coalesce_buf; scalar_t__ flags; scalar_t__ num_desc; int /*<<< orphan*/  list; TYPE_1__* descp; int /*<<< orphan*/  desc_limit; } ;
struct TYPE_2__ {int* qw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int EMSGSIZE ; 
 int ENODATA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_SDMA_PKT_SIZE ; 
 scalar_t__ SDMA_AHG_COPY ; 
 int SDMA_DESC0_FIRST_DESC_FLAG ; 
 int SDMA_DESC1_HEADER_INDEX_MASK ; 
 int SDMA_DESC1_HEADER_INDEX_SHIFT ; 
 int SDMA_DESC1_HEADER_MODE_MASK ; 
 int SDMA_DESC1_HEADER_MODE_SHIFT ; 
 scalar_t__ SDMA_TXREQ_F_AHG_COPY ; 
 scalar_t__ SDMA_TXREQ_F_USE_AHG ; 
 int /*<<< orphan*/  _sdma_txreq_ahgadd (struct sdma_txreq*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline int sdma_txinit_ahg(
	struct sdma_txreq *tx,
	u16 flags,
	u16 tlen,
	u8 ahg_entry,
	u8 num_ahg,
	u32 *ahg,
	u8 ahg_hlen,
	void (*cb)(struct sdma_txreq *, int))
{
	if (tlen == 0)
		return -ENODATA;
	if (tlen > MAX_SDMA_PKT_SIZE)
		return -EMSGSIZE;
	tx->desc_limit = ARRAY_SIZE(tx->descs);
	tx->descp = &tx->descs[0];
	INIT_LIST_HEAD(&tx->list);
	tx->num_desc = 0;
	tx->flags = flags;
	tx->complete = cb;
	tx->coalesce_buf = NULL;
	tx->wait = NULL;
	tx->packet_len = tlen;
	tx->tlen = tx->packet_len;
	tx->descs[0].qw[0] = SDMA_DESC0_FIRST_DESC_FLAG;
	tx->descs[0].qw[1] = 0;
	if (flags & SDMA_TXREQ_F_AHG_COPY)
		tx->descs[0].qw[1] |=
			(((u64)ahg_entry & SDMA_DESC1_HEADER_INDEX_MASK)
				<< SDMA_DESC1_HEADER_INDEX_SHIFT) |
			(((u64)SDMA_AHG_COPY & SDMA_DESC1_HEADER_MODE_MASK)
				<< SDMA_DESC1_HEADER_MODE_SHIFT);
	else if (flags & SDMA_TXREQ_F_USE_AHG && num_ahg)
		_sdma_txreq_ahgadd(tx, num_ahg, ahg_entry, ahg, ahg_hlen);
	return 0;
}