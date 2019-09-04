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
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  ver_tid_offset; } ;
struct TYPE_8__ {TYPE_3__ kdeth; } ;
struct TYPE_5__ {int fragsize; int /*<<< orphan*/  ctrl; } ;
struct user_sdma_request {int* tids; size_t tididx; TYPE_4__ hdr; TYPE_1__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/  ver_tid_offset; } ;
struct hfi1_pkt_header {TYPE_2__ kdeth; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int EINVAL ; 
 scalar_t__ EXPECTED ; 
 int EXP_TID_GET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDX ; 
 int KDETH_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KDETH_OM_LARGE ; 
 int KDETH_OM_SMALL ; 
 int /*<<< orphan*/  LEN ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  OM ; 
 int PAGE_SIZE ; 
 int PIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  TID ; 
 int /*<<< orphan*/  TIDCTRL ; 
 int get_lrh_len (struct hfi1_pkt_header,int) ; 
 scalar_t__ req_opcode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_header_template(struct user_sdma_request *req,
				 struct hfi1_pkt_header *hdr, u32 lrhlen,
				 u32 datalen)
{
	/*
	 * Perform safety checks for any type of packet:
	 *    - transfer size is multiple of 64bytes
	 *    - packet length is multiple of 4 bytes
	 *    - packet length is not larger than MTU size
	 *
	 * These checks are only done for the first packet of the
	 * transfer since the header is "given" to us by user space.
	 * For the remainder of the packets we compute the values.
	 */
	if (req->info.fragsize % PIO_BLOCK_SIZE || lrhlen & 0x3 ||
	    lrhlen > get_lrh_len(*hdr, req->info.fragsize))
		return -EINVAL;

	if (req_opcode(req->info.ctrl) == EXPECTED) {
		/*
		 * The header is checked only on the first packet. Furthermore,
		 * we ensure that at least one TID entry is copied when the
		 * request is submitted. Therefore, we don't have to verify that
		 * tididx points to something sane.
		 */
		u32 tidval = req->tids[req->tididx],
			tidlen = EXP_TID_GET(tidval, LEN) * PAGE_SIZE,
			tididx = EXP_TID_GET(tidval, IDX),
			tidctrl = EXP_TID_GET(tidval, CTRL),
			tidoff;
		__le32 kval = hdr->kdeth.ver_tid_offset;

		tidoff = KDETH_GET(kval, OFFSET) *
			  (KDETH_GET(req->hdr.kdeth.ver_tid_offset, OM) ?
			   KDETH_OM_LARGE : KDETH_OM_SMALL);
		/*
		 * Expected receive packets have the following
		 * additional checks:
		 *     - offset is not larger than the TID size
		 *     - TIDCtrl values match between header and TID array
		 *     - TID indexes match between header and TID array
		 */
		if ((tidoff + datalen > tidlen) ||
		    KDETH_GET(kval, TIDCTRL) != tidctrl ||
		    KDETH_GET(kval, TID) != tididx)
			return -EINVAL;
	}
	return 0;
}