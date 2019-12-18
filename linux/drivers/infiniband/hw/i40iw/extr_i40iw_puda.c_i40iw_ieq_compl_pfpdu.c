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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct list_head {int dummy; } ;
struct i40iw_puda_rsrc {int dummy; } ;
struct TYPE_2__ {scalar_t__ va; } ;
struct i40iw_puda_buf {scalar_t__ seqnum; scalar_t__ hdrlen; scalar_t__ datalen; int /*<<< orphan*/  list; TYPE_1__ mem; int /*<<< orphan*/ * data; scalar_t__ totallen; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_ieq_copy_to_txbuf (struct i40iw_puda_buf*,struct i40iw_puda_buf*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  i40iw_ieq_setup_tx_buf (struct i40iw_puda_buf*,struct i40iw_puda_buf*) ; 
 struct i40iw_puda_buf* i40iw_puda_get_listbuf (struct list_head*) ; 
 int /*<<< orphan*/  i40iw_puda_ret_bufpool (struct i40iw_puda_rsrc*,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void  i40iw_ieq_compl_pfpdu(struct i40iw_puda_rsrc *ieq,
				   struct list_head *rxlist,
				   struct list_head *pbufl,
				   struct i40iw_puda_buf *txbuf,
				   u16 fpdu_len)
{
	struct i40iw_puda_buf *buf;
	u32 nextseqnum;
	u16 txoffset, bufoffset;

	buf = i40iw_puda_get_listbuf(pbufl);
	if (!buf)
		return;
	nextseqnum = buf->seqnum + fpdu_len;
	txbuf->totallen = buf->hdrlen + fpdu_len;
	txbuf->data = (u8 *)txbuf->mem.va + buf->hdrlen;
	i40iw_ieq_setup_tx_buf(buf, txbuf);

	txoffset = buf->hdrlen;
	bufoffset = (u16)(buf->data - (u8 *)buf->mem.va);

	do {
		if (buf->datalen >= fpdu_len) {
			/* copied full fpdu */
			i40iw_ieq_copy_to_txbuf(buf, txbuf, bufoffset, txoffset, fpdu_len);
			buf->datalen -= fpdu_len;
			buf->data += fpdu_len;
			buf->seqnum = nextseqnum;
			break;
		}
		/* copy partial fpdu */
		i40iw_ieq_copy_to_txbuf(buf, txbuf, bufoffset, txoffset, buf->datalen);
		txoffset += buf->datalen;
		fpdu_len -= buf->datalen;
		i40iw_puda_ret_bufpool(ieq, buf);
		buf = i40iw_puda_get_listbuf(pbufl);
		if (!buf)
			return;
		bufoffset = (u16)(buf->data - (u8 *)buf->mem.va);
	} while (1);

	/* last buffer on the list*/
	if (buf->datalen)
		list_add(&buf->list, rxlist);
	else
		i40iw_puda_ret_bufpool(ieq, buf);
}