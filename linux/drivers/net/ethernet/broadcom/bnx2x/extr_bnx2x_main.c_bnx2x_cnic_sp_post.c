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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  conn_and_cmd_data; int /*<<< orphan*/  type; } ;
struct eth_spe {TYPE_1__ hdr; } ;
struct TYPE_8__ {int max_kwqe_pending; } ;
struct bnx2x {int cnic_spq_pending; int /*<<< orphan*/  spq_lock; struct eth_spe* cnic_kwq_cons; struct eth_spe* cnic_kwq; struct eth_spe* cnic_kwq_last; scalar_t__ cnic_kwq_pending; TYPE_4__ cnic_eth_dev; int /*<<< orphan*/  eq_spq_left; int /*<<< orphan*/  cq_spq_left; TYPE_3__* context; int /*<<< orphan*/  panic; } ;
struct TYPE_7__ {TYPE_2__* vcxt; } ;
struct TYPE_6__ {int /*<<< orphan*/  eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int BNX2X_ISCSI_ETH_CID (struct bnx2x*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,scalar_t__,int) ; 
 scalar_t__ ETH_CONNECTION_TYPE ; 
 scalar_t__ FCOE_CONNECTION_TYPE ; 
 int ILT_PAGE_CIDS ; 
 scalar_t__ ISCSI_CONNECTION_TYPE ; 
 scalar_t__ NONE_CONNECTION_TYPE ; 
 scalar_t__ RAMROD_CMD_ID_ETH_CLIENT_SETUP ; 
 int SPE_HDR_CMD_ID_SHIFT ; 
 scalar_t__ SPE_HDR_CONN_TYPE ; 
 scalar_t__ SPE_HDR_CONN_TYPE_SHIFT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 int /*<<< orphan*/  bnx2x_set_ctx_validation (struct bnx2x*,int /*<<< orphan*/ *,int) ; 
 struct eth_spe* bnx2x_sp_get_next (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_sp_prod_update (struct bnx2x*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_cnic_sp_post(struct bnx2x *bp, int count)
{
	struct eth_spe *spe;
	int cxt_index, cxt_offset;

#ifdef BNX2X_STOP_ON_ERROR
	if (unlikely(bp->panic))
		return;
#endif

	spin_lock_bh(&bp->spq_lock);
	BUG_ON(bp->cnic_spq_pending < count);
	bp->cnic_spq_pending -= count;

	for (; bp->cnic_kwq_pending; bp->cnic_kwq_pending--) {
		u16 type =  (le16_to_cpu(bp->cnic_kwq_cons->hdr.type)
				& SPE_HDR_CONN_TYPE) >>
				SPE_HDR_CONN_TYPE_SHIFT;
		u8 cmd = (le32_to_cpu(bp->cnic_kwq_cons->hdr.conn_and_cmd_data)
				>> SPE_HDR_CMD_ID_SHIFT) & 0xff;

		/* Set validation for iSCSI L2 client before sending SETUP
		 *  ramrod
		 */
		if (type == ETH_CONNECTION_TYPE) {
			if (cmd == RAMROD_CMD_ID_ETH_CLIENT_SETUP) {
				cxt_index = BNX2X_ISCSI_ETH_CID(bp) /
					ILT_PAGE_CIDS;
				cxt_offset = BNX2X_ISCSI_ETH_CID(bp) -
					(cxt_index * ILT_PAGE_CIDS);
				bnx2x_set_ctx_validation(bp,
					&bp->context[cxt_index].
							 vcxt[cxt_offset].eth,
					BNX2X_ISCSI_ETH_CID(bp));
			}
		}

		/*
		 * There may be not more than 8 L2, not more than 8 L5 SPEs
		 * and in the air. We also check that number of outstanding
		 * COMMON ramrods is not more than the EQ and SPQ can
		 * accommodate.
		 */
		if (type == ETH_CONNECTION_TYPE) {
			if (!atomic_read(&bp->cq_spq_left))
				break;
			else
				atomic_dec(&bp->cq_spq_left);
		} else if (type == NONE_CONNECTION_TYPE) {
			if (!atomic_read(&bp->eq_spq_left))
				break;
			else
				atomic_dec(&bp->eq_spq_left);
		} else if ((type == ISCSI_CONNECTION_TYPE) ||
			   (type == FCOE_CONNECTION_TYPE)) {
			if (bp->cnic_spq_pending >=
			    bp->cnic_eth_dev.max_kwqe_pending)
				break;
			else
				bp->cnic_spq_pending++;
		} else {
			BNX2X_ERR("Unknown SPE type: %d\n", type);
			bnx2x_panic();
			break;
		}

		spe = bnx2x_sp_get_next(bp);
		*spe = *bp->cnic_kwq_cons;

		DP(BNX2X_MSG_SP, "pending on SPQ %d, on KWQ %d count %d\n",
		   bp->cnic_spq_pending, bp->cnic_kwq_pending, count);

		if (bp->cnic_kwq_cons == bp->cnic_kwq_last)
			bp->cnic_kwq_cons = bp->cnic_kwq;
		else
			bp->cnic_kwq_cons++;
	}
	bnx2x_sp_prod_update(bp);
	spin_unlock_bh(&bp->spq_lock);
}