#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {void* nr_regions; } ;
struct TYPE_3__ {void* nr_windows; } ;
struct iproc_pcie {int type; int has_apb_err_disable; int iproc_cfg_read; int need_msi_steer; int ep_is_internal; int rej_unconfig_pf; scalar_t__* reg_offsets; void* ib_map; TYPE_2__ ib; TYPE_1__ ob; void* ob_map; int /*<<< orphan*/  need_ob_cfg; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CFG_RETRY_STATUS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IPROC_PCIE_MAX_NUM_REG ; 
#define  IPROC_PCIE_PAXB 132 
#define  IPROC_PCIE_PAXB_BCMA 131 
#define  IPROC_PCIE_PAXB_V2 130 
#define  IPROC_PCIE_PAXC 129 
#define  IPROC_PCIE_PAXC_V2 128 
 scalar_t__ const IPROC_PCIE_REG_INVALID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__* devm_kcalloc (struct device*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__* iproc_pcie_reg_paxb ; 
 scalar_t__* iproc_pcie_reg_paxb_bcma ; 
 scalar_t__* iproc_pcie_reg_paxb_v2 ; 
 scalar_t__* iproc_pcie_reg_paxc ; 
 scalar_t__* iproc_pcie_reg_paxc_v2 ; 
 void* paxb_ob_map ; 
 void* paxb_v2_ib_map ; 
 void* paxb_v2_ob_map ; 

__attribute__((used)) static int iproc_pcie_rev_init(struct iproc_pcie *pcie)
{
	struct device *dev = pcie->dev;
	unsigned int reg_idx;
	const u16 *regs;

	switch (pcie->type) {
	case IPROC_PCIE_PAXB_BCMA:
		regs = iproc_pcie_reg_paxb_bcma;
		break;
	case IPROC_PCIE_PAXB:
		regs = iproc_pcie_reg_paxb;
		pcie->has_apb_err_disable = true;
		if (pcie->need_ob_cfg) {
			pcie->ob_map = paxb_ob_map;
			pcie->ob.nr_windows = ARRAY_SIZE(paxb_ob_map);
		}
		break;
	case IPROC_PCIE_PAXB_V2:
		regs = iproc_pcie_reg_paxb_v2;
		pcie->iproc_cfg_read = true;
		pcie->has_apb_err_disable = true;
		if (pcie->need_ob_cfg) {
			pcie->ob_map = paxb_v2_ob_map;
			pcie->ob.nr_windows = ARRAY_SIZE(paxb_v2_ob_map);
		}
		pcie->ib.nr_regions = ARRAY_SIZE(paxb_v2_ib_map);
		pcie->ib_map = paxb_v2_ib_map;
		pcie->need_msi_steer = true;
		dev_warn(dev, "reads of config registers that contain %#x return incorrect data\n",
			 CFG_RETRY_STATUS);
		break;
	case IPROC_PCIE_PAXC:
		regs = iproc_pcie_reg_paxc;
		pcie->ep_is_internal = true;
		pcie->iproc_cfg_read = true;
		pcie->rej_unconfig_pf = true;
		break;
	case IPROC_PCIE_PAXC_V2:
		regs = iproc_pcie_reg_paxc_v2;
		pcie->ep_is_internal = true;
		pcie->iproc_cfg_read = true;
		pcie->rej_unconfig_pf = true;
		pcie->need_msi_steer = true;
		break;
	default:
		dev_err(dev, "incompatible iProc PCIe interface\n");
		return -EINVAL;
	}

	pcie->reg_offsets = devm_kcalloc(dev, IPROC_PCIE_MAX_NUM_REG,
					 sizeof(*pcie->reg_offsets),
					 GFP_KERNEL);
	if (!pcie->reg_offsets)
		return -ENOMEM;

	/* go through the register table and populate all valid registers */
	pcie->reg_offsets[0] = (pcie->type == IPROC_PCIE_PAXC_V2) ?
		IPROC_PCIE_REG_INVALID : regs[0];
	for (reg_idx = 1; reg_idx < IPROC_PCIE_MAX_NUM_REG; reg_idx++)
		pcie->reg_offsets[reg_idx] = regs[reg_idx] ?
			regs[reg_idx] : IPROC_PCIE_REG_INVALID;

	return 0;
}