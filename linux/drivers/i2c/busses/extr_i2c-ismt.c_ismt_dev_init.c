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
struct ismt_priv {int /*<<< orphan*/  cmp; scalar_t__ head; int /*<<< orphan*/  hw; int /*<<< orphan*/  io_rng_dma; TYPE_1__* pci_dev; } ;
struct ismt_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISMT_DESC_ENTRIES ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ismt_dev_init(struct ismt_priv *priv)
{
	/* allocate memory for the descriptor */
	priv->hw = dmam_alloc_coherent(&priv->pci_dev->dev,
				       (ISMT_DESC_ENTRIES
					       * sizeof(struct ismt_desc)),
				       &priv->io_rng_dma,
				       GFP_KERNEL);
	if (!priv->hw)
		return -ENOMEM;

	priv->head = 0;
	init_completion(&priv->cmp);

	return 0;
}