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
struct TYPE_4__ {int /*<<< orphan*/  rx_q; int /*<<< orphan*/  rx_wq; int /*<<< orphan*/  rx_work; } ;
struct nfcmrvl_private {TYPE_1__ fw_dnld; TYPE_3__* ndev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_6__ {TYPE_2__* nfc_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_dnld_rx_work ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int	nfcmrvl_fw_dnld_init(struct nfcmrvl_private *priv)
{
	char name[32];

	INIT_WORK(&priv->fw_dnld.rx_work, fw_dnld_rx_work);
	snprintf(name, sizeof(name), "%s_nfcmrvl_fw_dnld_rx_wq",
		 dev_name(&priv->ndev->nfc_dev->dev));
	priv->fw_dnld.rx_wq = create_singlethread_workqueue(name);
	if (!priv->fw_dnld.rx_wq)
		return -ENOMEM;
	skb_queue_head_init(&priv->fw_dnld.rx_q);
	return 0;
}