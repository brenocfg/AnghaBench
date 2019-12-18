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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mei_me_hw {struct mei_cfg const* cfg; } ;
struct mei_device {int /*<<< orphan*/  fw_f_fw_ver_supported; TYPE_1__* dr_dscr; } ;
struct mei_cfg {int /*<<< orphan*/  fw_ver_supported; int /*<<< orphan*/ * dma_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int DMA_DSCR_NUM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mei_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_device_init (struct mei_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_me_hw_ops ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 

struct mei_device *mei_me_dev_init(struct pci_dev *pdev,
				   const struct mei_cfg *cfg)
{
	struct mei_device *dev;
	struct mei_me_hw *hw;
	int i;

	dev = devm_kzalloc(&pdev->dev, sizeof(struct mei_device) +
			   sizeof(struct mei_me_hw), GFP_KERNEL);
	if (!dev)
		return NULL;

	hw = to_me_hw(dev);

	for (i = 0; i < DMA_DSCR_NUM; i++)
		dev->dr_dscr[i].size = cfg->dma_size[i];

	mei_device_init(dev, &pdev->dev, &mei_me_hw_ops);
	hw->cfg = cfg;

	dev->fw_f_fw_ver_supported = cfg->fw_ver_supported;

	return dev;
}