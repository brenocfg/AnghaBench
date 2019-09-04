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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mei_me_hw {struct mei_cfg const* cfg; } ;
struct mei_device {int dummy; } ;
struct mei_cfg {int dummy; } ;

/* Variables and functions */
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

	dev = devm_kzalloc(&pdev->dev, sizeof(struct mei_device) +
			   sizeof(struct mei_me_hw), GFP_KERNEL);
	if (!dev)
		return NULL;
	hw = to_me_hw(dev);

	mei_device_init(dev, &pdev->dev, &mei_me_hw_ops);
	hw->cfg = cfg;
	return dev;
}