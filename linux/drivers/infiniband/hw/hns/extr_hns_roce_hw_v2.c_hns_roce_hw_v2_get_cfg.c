#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hns_roce_v2_priv {struct hnae3_handle* handle; } ;
struct TYPE_11__ {TYPE_3__** netdevs; scalar_t__* phy_port; } ;
struct TYPE_9__ {int /*<<< orphan*/  node_guid; } ;
struct TYPE_8__ {int num_ports; } ;
struct hns_roce_dev {int cmd_mod; int /*<<< orphan*/  reset_cnt; scalar_t__ loop_idc; int /*<<< orphan*/ * irq; TYPE_4__ iboe; TYPE_2__ ib_dev; TYPE_1__ caps; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  sdb_offset; int /*<<< orphan*/  odb_offset; int /*<<< orphan*/ * dfx; int /*<<< orphan*/ * hw; struct hns_roce_v2_priv* priv; } ;
struct TYPE_12__ {scalar_t__ base_vector; TYPE_3__* netdev; int /*<<< orphan*/  roce_io_base; } ;
struct hnae3_handle {TYPE_7__* ae_algo; TYPE_5__ rinfo; int /*<<< orphan*/  pdev; } ;
struct TYPE_14__ {TYPE_6__* ops; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* ae_dev_reset_cnt ) (struct hnae3_handle*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int HNS_ROCE_V2_MAX_IRQ_NUM ; 
 int /*<<< orphan*/  ROCEE_DB_SQ_L_0_REG ; 
 int /*<<< orphan*/  addrconf_addr_eui48 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_dfx_hw_v2 ; 
 int /*<<< orphan*/  hns_roce_hw_v2 ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns_roce_hw_v2_get_cfg(struct hns_roce_dev *hr_dev,
				  struct hnae3_handle *handle)
{
	struct hns_roce_v2_priv *priv = hr_dev->priv;
	int i;

	hr_dev->hw = &hns_roce_hw_v2;
	hr_dev->dfx = &hns_roce_dfx_hw_v2;
	hr_dev->sdb_offset = ROCEE_DB_SQ_L_0_REG;
	hr_dev->odb_offset = hr_dev->sdb_offset;

	/* Get info from NIC driver. */
	hr_dev->reg_base = handle->rinfo.roce_io_base;
	hr_dev->caps.num_ports = 1;
	hr_dev->iboe.netdevs[0] = handle->rinfo.netdev;
	hr_dev->iboe.phy_port[0] = 0;

	addrconf_addr_eui48((u8 *)&hr_dev->ib_dev.node_guid,
			    hr_dev->iboe.netdevs[0]->dev_addr);

	for (i = 0; i < HNS_ROCE_V2_MAX_IRQ_NUM; i++)
		hr_dev->irq[i] = pci_irq_vector(handle->pdev,
						i + handle->rinfo.base_vector);

	/* cmd issue mode: 0 is poll, 1 is event */
	hr_dev->cmd_mod = 1;
	hr_dev->loop_idc = 0;

	hr_dev->reset_cnt = handle->ae_algo->ops->ae_dev_reset_cnt(handle);
	priv->handle = handle;

	return 0;
}