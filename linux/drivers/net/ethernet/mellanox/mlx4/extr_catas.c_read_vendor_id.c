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
typedef  int u16 ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int read_vendor_id(struct mlx4_dev *dev)
{
	u16 vendor_id = 0;
	int ret;

	ret = pci_read_config_word(dev->persist->pdev, 0, &vendor_id);
	if (ret) {
		mlx4_err(dev, "Failed to read vendor ID, ret=%d\n", ret);
		return ret;
	}

	if (vendor_id == 0xffff) {
		mlx4_err(dev, "PCI can't be accessed to read vendor id\n");
		return -EINVAL;
	}

	return 0;
}