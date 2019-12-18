#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hnae3_client {TYPE_4__* ops; } ;
struct hnae3_ae_dev {TYPE_2__* pdev; struct hclge_dev* priv; } ;
struct TYPE_11__ {struct hnae3_client* client; } ;
struct hclge_vport {TYPE_5__ nic; } ;
struct TYPE_7__ {int reset_cnt; } ;
struct hclge_dev {int /*<<< orphan*/  state; TYPE_3__* vport; TYPE_1__ rst_stats; } ;
struct TYPE_10__ {int (* init_instance ) (TYPE_5__*) ;int /*<<< orphan*/  (* uninit_instance ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  nic; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGE_STATE_NIC_REGISTERED ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 int /*<<< orphan*/  HCLGE_WAIT_RESET_DONE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_config_nic_hw_error (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_info_show (struct hclge_dev*) ; 
 int /*<<< orphan*/  hnae3_set_client_init_flag (struct hnae3_client*,struct hnae3_ae_dev*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_drv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_init_nic_client_instance(struct hnae3_ae_dev *ae_dev,
					  struct hclge_vport *vport)
{
	struct hnae3_client *client = vport->nic.client;
	struct hclge_dev *hdev = ae_dev->priv;
	int rst_cnt;
	int ret;

	rst_cnt = hdev->rst_stats.reset_cnt;
	ret = client->ops->init_instance(&vport->nic);
	if (ret)
		return ret;

	set_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state);
	if (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) ||
	    rst_cnt != hdev->rst_stats.reset_cnt) {
		ret = -EBUSY;
		goto init_nic_err;
	}

	/* Enable nic hw error interrupts */
	ret = hclge_config_nic_hw_error(hdev, true);
	if (ret) {
		dev_err(&ae_dev->pdev->dev,
			"fail(%d) to enable hw error interrupts\n", ret);
		goto init_nic_err;
	}

	hnae3_set_client_init_flag(client, ae_dev, 1);

	if (netif_msg_drv(&hdev->vport->nic))
		hclge_info_show(hdev);

	return ret;

init_nic_err:
	clear_bit(HCLGE_STATE_NIC_REGISTERED, &hdev->state);
	while (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
		msleep(HCLGE_WAIT_RESET_DONE);

	client->ops->uninit_instance(&vport->nic, 0);

	return ret;
}