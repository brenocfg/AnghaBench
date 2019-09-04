#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ecr_base; } ;
struct TYPE_8__ {int /*<<< orphan*/  eq_arm; int /*<<< orphan*/  eq_set_ci_base; } ;
struct TYPE_10__ {TYPE_4__ tavor; TYPE_3__ arbel; } ;
struct TYPE_6__ {int clr_int_base; int eq_arm_base; int eq_set_ci_base; } ;
struct TYPE_7__ {TYPE_1__ arbel; } ;
struct mthca_dev {int /*<<< orphan*/  clr_base; TYPE_5__ eq_regs; TYPE_2__ fw; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MTHCA_CLR_INT_BASE ; 
 int MTHCA_CLR_INT_SIZE ; 
 int MTHCA_ECR_BASE ; 
 int MTHCA_ECR_CLR_SIZE ; 
 int MTHCA_ECR_SIZE ; 
 int MTHCA_EQ_SET_CI_SIZE ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 scalar_t__ mthca_map_reg (struct mthca_dev*,int,int,int /*<<< orphan*/ *) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_map_eq_regs(struct mthca_dev *dev)
{
	if (mthca_is_memfree(dev)) {
		/*
		 * We assume that the EQ arm and EQ set CI registers
		 * fall within the first BAR.  We can't trust the
		 * values firmware gives us, since those addresses are
		 * valid on the HCA's side of the PCI bus but not
		 * necessarily the host side.
		 */
		if (mthca_map_reg(dev, (pci_resource_len(dev->pdev, 0) - 1) &
				  dev->fw.arbel.clr_int_base, MTHCA_CLR_INT_SIZE,
				  &dev->clr_base)) {
			mthca_err(dev, "Couldn't map interrupt clear register, "
				  "aborting.\n");
			return -ENOMEM;
		}

		/*
		 * Add 4 because we limit ourselves to EQs 0 ... 31,
		 * so we only need the low word of the register.
		 */
		if (mthca_map_reg(dev, ((pci_resource_len(dev->pdev, 0) - 1) &
					dev->fw.arbel.eq_arm_base) + 4, 4,
				  &dev->eq_regs.arbel.eq_arm)) {
			mthca_err(dev, "Couldn't map EQ arm register, aborting.\n");
			iounmap(dev->clr_base);
			return -ENOMEM;
		}

		if (mthca_map_reg(dev, (pci_resource_len(dev->pdev, 0) - 1) &
				  dev->fw.arbel.eq_set_ci_base,
				  MTHCA_EQ_SET_CI_SIZE,
				  &dev->eq_regs.arbel.eq_set_ci_base)) {
			mthca_err(dev, "Couldn't map EQ CI register, aborting.\n");
			iounmap(dev->eq_regs.arbel.eq_arm);
			iounmap(dev->clr_base);
			return -ENOMEM;
		}
	} else {
		if (mthca_map_reg(dev, MTHCA_CLR_INT_BASE, MTHCA_CLR_INT_SIZE,
				  &dev->clr_base)) {
			mthca_err(dev, "Couldn't map interrupt clear register, "
				  "aborting.\n");
			return -ENOMEM;
		}

		if (mthca_map_reg(dev, MTHCA_ECR_BASE,
				  MTHCA_ECR_SIZE + MTHCA_ECR_CLR_SIZE,
				  &dev->eq_regs.tavor.ecr_base)) {
			mthca_err(dev, "Couldn't map ecr register, "
				  "aborting.\n");
			iounmap(dev->clr_base);
			return -ENOMEM;
		}
	}

	return 0;

}