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
typedef  int u8 ;
typedef  int u32 ;
struct mthca_mailbox {void const* buf; int /*<<< orphan*/  dma; } ;
struct mthca_dev {int dummy; } ;
struct ib_wc {int src_qp; int sl; int dlid_path_bits; int wc_flags; int pkey_index; int /*<<< orphan*/  slid; TYPE_1__* qp; } ;
typedef  void ib_grh ;
struct TYPE_2__ {int qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAD_IFC ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_C ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_WC_GRH ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int MAD_IFC_GRH_OFFSET ; 
 int /*<<< orphan*/  MAD_IFC_G_PATH_OFFSET ; 
 int /*<<< orphan*/  MAD_IFC_MY_QPN_OFFSET ; 
 int /*<<< orphan*/  MAD_IFC_PKEY_OFFSET ; 
 int /*<<< orphan*/  MAD_IFC_RLID_OFFSET ; 
 int /*<<< orphan*/  MAD_IFC_RQPN_OFFSET ; 
 int /*<<< orphan*/  MAD_IFC_SL_OFFSET ; 
 int /*<<< orphan*/  MTHCA_PUT (void*,int,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int ib_lid_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd_box (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 

int mthca_MAD_IFC(struct mthca_dev *dev, int ignore_mkey, int ignore_bkey,
		  int port, const struct ib_wc *in_wc, const struct ib_grh *in_grh,
		  const void *in_mad, void *response_mad)
{
	struct mthca_mailbox *inmailbox, *outmailbox;
	void *inbox;
	int err;
	u32 in_modifier = port;
	u8 op_modifier = 0;

#define MAD_IFC_BOX_SIZE      0x400
#define MAD_IFC_MY_QPN_OFFSET 0x100
#define MAD_IFC_RQPN_OFFSET   0x108
#define MAD_IFC_SL_OFFSET     0x10c
#define MAD_IFC_G_PATH_OFFSET 0x10d
#define MAD_IFC_RLID_OFFSET   0x10e
#define MAD_IFC_PKEY_OFFSET   0x112
#define MAD_IFC_GRH_OFFSET    0x140

	inmailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(inmailbox))
		return PTR_ERR(inmailbox);
	inbox = inmailbox->buf;

	outmailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(outmailbox)) {
		mthca_free_mailbox(dev, inmailbox);
		return PTR_ERR(outmailbox);
	}

	memcpy(inbox, in_mad, 256);

	/*
	 * Key check traps can't be generated unless we have in_wc to
	 * tell us where to send the trap.
	 */
	if (ignore_mkey || !in_wc)
		op_modifier |= 0x1;
	if (ignore_bkey || !in_wc)
		op_modifier |= 0x2;

	if (in_wc) {
		u8 val;

		memset(inbox + 256, 0, 256);

		MTHCA_PUT(inbox, in_wc->qp->qp_num, MAD_IFC_MY_QPN_OFFSET);
		MTHCA_PUT(inbox, in_wc->src_qp,     MAD_IFC_RQPN_OFFSET);

		val = in_wc->sl << 4;
		MTHCA_PUT(inbox, val,               MAD_IFC_SL_OFFSET);

		val = in_wc->dlid_path_bits |
			(in_wc->wc_flags & IB_WC_GRH ? 0x80 : 0);
		MTHCA_PUT(inbox, val,               MAD_IFC_G_PATH_OFFSET);

		MTHCA_PUT(inbox, ib_lid_cpu16(in_wc->slid), MAD_IFC_RLID_OFFSET);
		MTHCA_PUT(inbox, in_wc->pkey_index, MAD_IFC_PKEY_OFFSET);

		if (in_grh)
			memcpy(inbox + MAD_IFC_GRH_OFFSET, in_grh, 40);

		op_modifier |= 0x4;

		in_modifier |= ib_lid_cpu16(in_wc->slid) << 16;
	}

	err = mthca_cmd_box(dev, inmailbox->dma, outmailbox->dma,
			    in_modifier, op_modifier,
			    CMD_MAD_IFC, CMD_TIME_CLASS_C);

	if (!err)
		memcpy(response_mad, outmailbox->buf, 256);

	mthca_free_mailbox(dev, inmailbox);
	mthca_free_mailbox(dev, outmailbox);
	return err;
}