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
struct tcp_connect_and_offload_out {int /*<<< orphan*/  connection_handle; } ;
struct tcp_connect_and_offload_in_v1 {int dummy; } ;
struct tcp_connect_and_offload_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct beiscsi_hba {TYPE_2__ ctrl; struct iscsi_endpoint** ep_array; } ;
struct beiscsi_endpoint {scalar_t__ ep_cid; int cid_vld; int /*<<< orphan*/  fw_handle; struct beiscsi_hba* phba; } ;
struct be_dma_mem {unsigned int size; int /*<<< orphan*/  dma; int /*<<< orphan*/ * va; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 size_t BE_GET_CRI_FROM_CID (scalar_t__) ; 
 scalar_t__ BE_INVALID_CID ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_free_ep (struct beiscsi_endpoint*) ; 
 scalar_t__ beiscsi_get_cid (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,...) ; 
 int beiscsi_mccq_compl_wait (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,struct be_dma_mem*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_chip_be2_be3r (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int mgmt_open_connection (struct beiscsi_hba*,struct sockaddr*,struct beiscsi_endpoint*,struct be_dma_mem*) ; 

__attribute__((used)) static int beiscsi_open_conn(struct iscsi_endpoint *ep,
			     struct sockaddr *src_addr,
			     struct sockaddr *dst_addr, int non_blocking)
{
	struct beiscsi_endpoint *beiscsi_ep = ep->dd_data;
	struct beiscsi_hba *phba = beiscsi_ep->phba;
	struct tcp_connect_and_offload_out *ptcpcnct_out;
	struct be_dma_mem nonemb_cmd;
	unsigned int tag, req_memsize;
	int ret = -ENOMEM;

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_open_conn\n");

	beiscsi_ep->ep_cid = beiscsi_get_cid(phba);
	if (beiscsi_ep->ep_cid == BE_INVALID_CID) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : No free cid available\n");
		return ret;
	}

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_open_conn, ep_cid=%d\n",
		    beiscsi_ep->ep_cid);

	phba->ep_array[BE_GET_CRI_FROM_CID
		       (beiscsi_ep->ep_cid)] = ep;

	beiscsi_ep->cid_vld = 0;

	if (is_chip_be2_be3r(phba))
		req_memsize = sizeof(struct tcp_connect_and_offload_in);
	else
		req_memsize = sizeof(struct tcp_connect_and_offload_in_v1);

	nonemb_cmd.va = dma_alloc_coherent(&phba->ctrl.pdev->dev,
				req_memsize,
				&nonemb_cmd.dma, GFP_KERNEL);
	if (nonemb_cmd.va == NULL) {

		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Failed to allocate memory for"
			    " mgmt_open_connection\n");

		beiscsi_free_ep(beiscsi_ep);
		return -ENOMEM;
	}
	nonemb_cmd.size = req_memsize;
	memset(nonemb_cmd.va, 0, nonemb_cmd.size);
	tag = mgmt_open_connection(phba, dst_addr, beiscsi_ep, &nonemb_cmd);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : mgmt_open_connection Failed for cid=%d\n",
			    beiscsi_ep->ep_cid);

		dma_free_coherent(&phba->ctrl.pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
		beiscsi_free_ep(beiscsi_ep);
		return -EAGAIN;
	}

	ret = beiscsi_mccq_compl_wait(phba, tag, NULL, &nonemb_cmd);
	if (ret) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BS_%d : mgmt_open_connection Failed");

		if (ret != -EBUSY)
			dma_free_coherent(&phba->ctrl.pdev->dev,
					nonemb_cmd.size, nonemb_cmd.va,
					nonemb_cmd.dma);

		beiscsi_free_ep(beiscsi_ep);
		return ret;
	}

	ptcpcnct_out = (struct tcp_connect_and_offload_out *)nonemb_cmd.va;
	beiscsi_ep = ep->dd_data;
	beiscsi_ep->fw_handle = ptcpcnct_out->connection_handle;
	beiscsi_ep->cid_vld = 1;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : mgmt_open_connection Success\n");

	dma_free_coherent(&phba->ctrl.pdev->dev, nonemb_cmd.size,
			    nonemb_cmd.va, nonemb_cmd.dma);
	return 0;
}