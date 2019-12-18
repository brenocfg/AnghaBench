#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ rx_csum_offload; scalar_t__ tx_csum_offload; } ;
struct sxgbe_priv_data {TYPE_2__ hw_cap; TYPE_3__* hw; int /*<<< orphan*/  ioaddr; } ;
struct TYPE_7__ {int ctrl_uid; int ctrl_id; TYPE_1__* mac; } ;
struct TYPE_5__ {int (* get_controller_version ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sxgbe_get_hw_features (struct sxgbe_priv_data* const) ; 
 int /*<<< orphan*/  sxgbe_get_ops (TYPE_3__*) ; 

__attribute__((used)) static int sxgbe_hw_init(struct sxgbe_priv_data * const priv)
{
	u32 ctrl_ids;

	priv->hw = kmalloc(sizeof(*priv->hw), GFP_KERNEL);
	if(!priv->hw)
		return -ENOMEM;

	/* get the hardware ops */
	sxgbe_get_ops(priv->hw);

	/* get the controller id */
	ctrl_ids = priv->hw->mac->get_controller_version(priv->ioaddr);
	priv->hw->ctrl_uid = (ctrl_ids & 0x00ff0000) >> 16;
	priv->hw->ctrl_id = (ctrl_ids & 0x000000ff);
	pr_info("user ID: 0x%x, Controller ID: 0x%x\n",
		priv->hw->ctrl_uid, priv->hw->ctrl_id);

	/* get the H/W features */
	if (!sxgbe_get_hw_features(priv))
		pr_info("Hardware features not found\n");

	if (priv->hw_cap.tx_csum_offload)
		pr_info("TX Checksum offload supported\n");

	if (priv->hw_cap.rx_csum_offload)
		pr_info("RX Checksum offload supported\n");

	return 0;
}