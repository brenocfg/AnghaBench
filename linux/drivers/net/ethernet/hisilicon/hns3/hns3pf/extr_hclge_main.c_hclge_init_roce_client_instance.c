#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hnae3_client {TYPE_3__* ops; } ;
struct hnae3_ae_dev {TYPE_2__* pdev; struct hclge_dev* priv; } ;
struct TYPE_9__ {struct hnae3_client* client; } ;
struct hclge_vport {TYPE_4__ roce; } ;
struct TYPE_6__ {int reset_cnt; } ;
struct hclge_dev {struct hnae3_client* roce_client; int /*<<< orphan*/  state; TYPE_1__ rst_stats; int /*<<< orphan*/  nic_client; } ;
struct TYPE_8__ {int (* init_instance ) (TYPE_4__*) ;int /*<<< orphan*/  (* uninit_instance ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGE_STATE_ROCE_REGISTERED ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 int /*<<< orphan*/  HCLGE_WAIT_RESET_DONE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_config_rocee_ras_interrupt (struct hclge_dev*,int) ; 
 int hclge_init_roce_base_info (struct hclge_vport*) ; 
 int /*<<< orphan*/  hnae3_dev_roce_supported (struct hclge_dev*) ; 
 int /*<<< orphan*/  hnae3_set_client_init_flag (struct hnae3_client*,struct hnae3_ae_dev*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_init_roce_client_instance(struct hnae3_ae_dev *ae_dev,
					   struct hclge_vport *vport)
{
	struct hnae3_client *client = vport->roce.client;
	struct hclge_dev *hdev = ae_dev->priv;
	int rst_cnt;
	int ret;

	if (!hnae3_dev_roce_supported(hdev) || !hdev->roce_client ||
	    !hdev->nic_client)
		return 0;

	client = hdev->roce_client;
	ret = hclge_init_roce_base_info(vport);
	if (ret)
		return ret;

	rst_cnt = hdev->rst_stats.reset_cnt;
	ret = client->ops->init_instance(&vport->roce);
	if (ret)
		return ret;

	set_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state);
	if (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) ||
	    rst_cnt != hdev->rst_stats.reset_cnt) {
		ret = -EBUSY;
		goto init_roce_err;
	}

	/* Enable roce ras interrupts */
	ret = hclge_config_rocee_ras_interrupt(hdev, true);
	if (ret) {
		dev_err(&ae_dev->pdev->dev,
			"fail(%d) to enable roce ras interrupts\n", ret);
		goto init_roce_err;
	}

	hnae3_set_client_init_flag(client, ae_dev, 1);

	return 0;

init_roce_err:
	clear_bit(HCLGE_STATE_ROCE_REGISTERED, &hdev->state);
	while (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state))
		msleep(HCLGE_WAIT_RESET_DONE);

	hdev->roce_client->ops->uninit_instance(&vport->roce, 0);

	return ret;
}