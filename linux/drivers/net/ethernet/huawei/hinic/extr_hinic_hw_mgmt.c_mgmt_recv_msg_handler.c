#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_recv_msg {size_t mod; int /*<<< orphan*/  msg_id; int /*<<< orphan*/  cmd; int /*<<< orphan*/  async_mgmt_to_pf; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg; int /*<<< orphan*/ * buf_out; } ;
struct hinic_pf_to_mgmt {struct hinic_mgmt_cb* mgmt_cb; struct hinic_hwif* hwif; } ;
struct hinic_mgmt_cb {unsigned long state; int /*<<< orphan*/  handle; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 unsigned long HINIC_MGMT_CB_ENABLED ; 
 unsigned long HINIC_MGMT_CB_RUNNING ; 
 size_t HINIC_MOD_MAX ; 
 int /*<<< orphan*/  MGMT_RESP ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  msg_to_mgmt_async (struct hinic_pf_to_mgmt*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgmt_recv_msg_handler(struct hinic_pf_to_mgmt *pf_to_mgmt,
				  struct hinic_recv_msg *recv_msg)
{
	struct hinic_hwif *hwif = pf_to_mgmt->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u8 *buf_out = recv_msg->buf_out;
	struct hinic_mgmt_cb *mgmt_cb;
	unsigned long cb_state;
	u16 out_size = 0;

	if (recv_msg->mod >= HINIC_MOD_MAX) {
		dev_err(&pdev->dev, "Unknown MGMT MSG module = %d\n",
			recv_msg->mod);
		return;
	}

	mgmt_cb = &pf_to_mgmt->mgmt_cb[recv_msg->mod];

	cb_state = cmpxchg(&mgmt_cb->state,
			   HINIC_MGMT_CB_ENABLED,
			   HINIC_MGMT_CB_ENABLED | HINIC_MGMT_CB_RUNNING);

	if ((cb_state == HINIC_MGMT_CB_ENABLED) && (mgmt_cb->cb))
		mgmt_cb->cb(mgmt_cb->handle, recv_msg->cmd,
			    recv_msg->msg, recv_msg->msg_len,
			    buf_out, &out_size);
	else
		dev_err(&pdev->dev, "No MGMT msg handler, mod = %d\n",
			recv_msg->mod);

	mgmt_cb->state &= ~HINIC_MGMT_CB_RUNNING;

	if (!recv_msg->async_mgmt_to_pf)
		/* MGMT sent sync msg, send the response */
		msg_to_mgmt_async(pf_to_mgmt, recv_msg->mod, recv_msg->cmd,
				  buf_out, out_size, MGMT_RESP,
				  recv_msg->msg_id);
}