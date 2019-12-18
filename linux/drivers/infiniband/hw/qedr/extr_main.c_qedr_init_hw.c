#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qedr_dev {int num_cnq; int /*<<< orphan*/  dpi; int /*<<< orphan*/  db_size; int /*<<< orphan*/  db_phys_addr; int /*<<< orphan*/  db_addr; int /*<<< orphan*/  rdma_ctx; TYPE_3__* ops; int /*<<< orphan*/  cdev; TYPE_2__* ndev; int /*<<< orphan*/  iwarp_max_mtu; TYPE_1__* cnq_array; } ;
struct qed_rdma_start_in_params {int desired_cnq; int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  cq_mode; struct qed_rdma_events* events; struct qed_rdma_cnq_params* cnq_pbl_list; } ;
struct qed_rdma_events {struct qedr_dev* context; int /*<<< orphan*/  unaffiliated_event; int /*<<< orphan*/  affiliated_event; } ;
struct qed_rdma_cnq_params {scalar_t__ pbl_ptr; int /*<<< orphan*/  num_pbl_pages; } ;
struct qed_rdma_add_user_out_params {int /*<<< orphan*/  dpi; int /*<<< orphan*/  dpi_size; int /*<<< orphan*/  dpi_phys_addr; int /*<<< orphan*/  dpi_addr; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int (* rdma_init ) (int /*<<< orphan*/ ,struct qed_rdma_start_in_params*) ;int (* rdma_add_user ) (int /*<<< orphan*/ ,struct qed_rdma_add_user_out_params*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct TYPE_4__ {int /*<<< orphan*/  pbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_RDMA_CQ_MODE_32_BITS ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_rdma_start_in_params*) ; 
 struct qed_rdma_start_in_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_get_page_cnt (int /*<<< orphan*/ *) ; 
 scalar_t__ qed_chain_get_pbl_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedr_affiliated_event ; 
 int qedr_set_device_attr (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_unaffiliated_event ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_rdma_start_in_params*) ; 
 int stub2 (int /*<<< orphan*/ ,struct qed_rdma_add_user_out_params*) ; 

__attribute__((used)) static int qedr_init_hw(struct qedr_dev *dev)
{
	struct qed_rdma_add_user_out_params out_params;
	struct qed_rdma_start_in_params *in_params;
	struct qed_rdma_cnq_params *cur_pbl;
	struct qed_rdma_events events;
	dma_addr_t p_phys_table;
	u32 page_cnt;
	int rc = 0;
	int i;

	in_params =  kzalloc(sizeof(*in_params), GFP_KERNEL);
	if (!in_params) {
		rc = -ENOMEM;
		goto out;
	}

	in_params->desired_cnq = dev->num_cnq;
	for (i = 0; i < dev->num_cnq; i++) {
		cur_pbl = &in_params->cnq_pbl_list[i];

		page_cnt = qed_chain_get_page_cnt(&dev->cnq_array[i].pbl);
		cur_pbl->num_pbl_pages = page_cnt;

		p_phys_table = qed_chain_get_pbl_phys(&dev->cnq_array[i].pbl);
		cur_pbl->pbl_ptr = (u64)p_phys_table;
	}

	events.affiliated_event = qedr_affiliated_event;
	events.unaffiliated_event = qedr_unaffiliated_event;
	events.context = dev;

	in_params->events = &events;
	in_params->cq_mode = QED_RDMA_CQ_MODE_32_BITS;
	in_params->max_mtu = dev->ndev->mtu;
	dev->iwarp_max_mtu = dev->ndev->mtu;
	ether_addr_copy(&in_params->mac_addr[0], dev->ndev->dev_addr);

	rc = dev->ops->rdma_init(dev->cdev, in_params);
	if (rc)
		goto out;

	rc = dev->ops->rdma_add_user(dev->rdma_ctx, &out_params);
	if (rc)
		goto out;

	dev->db_addr = out_params.dpi_addr;
	dev->db_phys_addr = out_params.dpi_phys_addr;
	dev->db_size = out_params.dpi_size;
	dev->dpi = out_params.dpi;

	rc = qedr_set_device_attr(dev);
out:
	kfree(in_params);
	if (rc)
		DP_ERR(dev, "Init HW Failed rc = %d\n", rc);

	return rc;
}