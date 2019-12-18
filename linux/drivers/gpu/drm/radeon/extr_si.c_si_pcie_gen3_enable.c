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
typedef  int u32 ;
typedef  int u16 ;
struct radeon_device {int flags; int usec_timeout; struct pci_dev* pdev; } ;
struct pci_dev {TYPE_1__* bus; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int LC_CURRENT_DATA_RATE_MASK ; 
 int LC_CURRENT_DATA_RATE_SHIFT ; 
 int LC_DETECTED_LINK_WIDTH_MASK ; 
 int LC_DETECTED_LINK_WIDTH_SHIFT ; 
 int LC_FORCE_DIS_HW_SPEED_CHANGE ; 
 int LC_FORCE_DIS_SW_SPEED_CHANGE ; 
 int LC_FORCE_EN_SW_SPEED_CHANGE ; 
 int LC_INITIATE_LINK_SPEED_CHANGE ; 
 int LC_LINK_WIDTH_MASK ; 
 int LC_LINK_WIDTH_SHIFT ; 
 int LC_OPERATING_LINK_WIDTH_MASK ; 
 int LC_OPERATING_LINK_WIDTH_SHIFT ; 
 int LC_RECONFIG_NOW ; 
 int LC_REDO_EQ ; 
 int LC_RENEGOTIATE_EN ; 
 int LC_RENEGOTIATION_SUPPORT ; 
 int LC_SET_QUIESCE ; 
 int LC_UPCONFIGURE_DIS ; 
 int LC_UPCONFIGURE_SUPPORT ; 
 int /*<<< orphan*/  PCIE_LC_CNTL4 ; 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_SPEED_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_STATUS1 ; 
 int PCIE_SPEED_5_0GT ; 
 int PCIE_SPEED_8_0GT ; 
 scalar_t__ PCI_EXP_DEVSTA ; 
 int PCI_EXP_DEVSTA_TRPND ; 
 scalar_t__ PCI_EXP_LNKCTL ; 
 scalar_t__ PCI_EXP_LNKCTL2 ; 
 int PCI_EXP_LNKCTL_HAWD ; 
 int PCI_SPEED_UNKNOWN ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 
 int pci_pcie_cap (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 int pcie_get_speed_cap (struct pci_dev*) ; 
 scalar_t__ radeon_pcie_gen2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void si_pcie_gen3_enable(struct radeon_device *rdev)
{
	struct pci_dev *root = rdev->pdev->bus->self;
	enum pci_bus_speed speed_cap;
	int bridge_pos, gpu_pos;
	u32 speed_cntl, current_data_rate;
	int i;
	u16 tmp16;

	if (pci_is_root_bus(rdev->pdev->bus))
		return;

	if (radeon_pcie_gen2 == 0)
		return;

	if (rdev->flags & RADEON_IS_IGP)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	speed_cap = pcie_get_speed_cap(root);
	if (speed_cap == PCI_SPEED_UNKNOWN)
		return;

	if ((speed_cap != PCIE_SPEED_8_0GT) &&
	    (speed_cap != PCIE_SPEED_5_0GT))
		return;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	current_data_rate = (speed_cntl & LC_CURRENT_DATA_RATE_MASK) >>
		LC_CURRENT_DATA_RATE_SHIFT;
	if (speed_cap == PCIE_SPEED_8_0GT) {
		if (current_data_rate == 2) {
			DRM_INFO("PCIE gen 3 link speeds already enabled\n");
			return;
		}
		DRM_INFO("enabling PCIE gen 3 link speeds, disable with radeon.pcie_gen2=0\n");
	} else if (speed_cap == PCIE_SPEED_5_0GT) {
		if (current_data_rate == 1) {
			DRM_INFO("PCIE gen 2 link speeds already enabled\n");
			return;
		}
		DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");
	}

	bridge_pos = pci_pcie_cap(root);
	if (!bridge_pos)
		return;

	gpu_pos = pci_pcie_cap(rdev->pdev);
	if (!gpu_pos)
		return;

	if (speed_cap == PCIE_SPEED_8_0GT) {
		/* re-try equalization if gen3 is not already enabled */
		if (current_data_rate != 2) {
			u16 bridge_cfg, gpu_cfg;
			u16 bridge_cfg2, gpu_cfg2;
			u32 max_lw, current_lw, tmp;

			pci_read_config_word(root, bridge_pos + PCI_EXP_LNKCTL, &bridge_cfg);
			pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL, &gpu_cfg);

			tmp16 = bridge_cfg | PCI_EXP_LNKCTL_HAWD;
			pci_write_config_word(root, bridge_pos + PCI_EXP_LNKCTL, tmp16);

			tmp16 = gpu_cfg | PCI_EXP_LNKCTL_HAWD;
			pci_write_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL, tmp16);

			tmp = RREG32_PCIE(PCIE_LC_STATUS1);
			max_lw = (tmp & LC_DETECTED_LINK_WIDTH_MASK) >> LC_DETECTED_LINK_WIDTH_SHIFT;
			current_lw = (tmp & LC_OPERATING_LINK_WIDTH_MASK) >> LC_OPERATING_LINK_WIDTH_SHIFT;

			if (current_lw < max_lw) {
				tmp = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
				if (tmp & LC_RENEGOTIATION_SUPPORT) {
					tmp &= ~(LC_LINK_WIDTH_MASK | LC_UPCONFIGURE_DIS);
					tmp |= (max_lw << LC_LINK_WIDTH_SHIFT);
					tmp |= LC_UPCONFIGURE_SUPPORT | LC_RENEGOTIATE_EN | LC_RECONFIG_NOW;
					WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, tmp);
				}
			}

			for (i = 0; i < 10; i++) {
				/* check status */
				pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_DEVSTA, &tmp16);
				if (tmp16 & PCI_EXP_DEVSTA_TRPND)
					break;

				pci_read_config_word(root, bridge_pos + PCI_EXP_LNKCTL, &bridge_cfg);
				pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL, &gpu_cfg);

				pci_read_config_word(root, bridge_pos + PCI_EXP_LNKCTL2, &bridge_cfg2);
				pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL2, &gpu_cfg2);

				tmp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				tmp |= LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, tmp);

				tmp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				tmp |= LC_REDO_EQ;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, tmp);

				msleep(100);

				/* linkctl */
				pci_read_config_word(root, bridge_pos + PCI_EXP_LNKCTL, &tmp16);
				tmp16 &= ~PCI_EXP_LNKCTL_HAWD;
				tmp16 |= (bridge_cfg & PCI_EXP_LNKCTL_HAWD);
				pci_write_config_word(root, bridge_pos + PCI_EXP_LNKCTL, tmp16);

				pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL, &tmp16);
				tmp16 &= ~PCI_EXP_LNKCTL_HAWD;
				tmp16 |= (gpu_cfg & PCI_EXP_LNKCTL_HAWD);
				pci_write_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL, tmp16);

				/* linkctl2 */
				pci_read_config_word(root, bridge_pos + PCI_EXP_LNKCTL2, &tmp16);
				tmp16 &= ~((1 << 4) | (7 << 9));
				tmp16 |= (bridge_cfg2 & ((1 << 4) | (7 << 9)));
				pci_write_config_word(root, bridge_pos + PCI_EXP_LNKCTL2, tmp16);

				pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL2, &tmp16);
				tmp16 &= ~((1 << 4) | (7 << 9));
				tmp16 |= (gpu_cfg2 & ((1 << 4) | (7 << 9)));
				pci_write_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL2, tmp16);

				tmp = RREG32_PCIE_PORT(PCIE_LC_CNTL4);
				tmp &= ~LC_SET_QUIESCE;
				WREG32_PCIE_PORT(PCIE_LC_CNTL4, tmp);
			}
		}
	}

	/* set the link speed */
	speed_cntl |= LC_FORCE_EN_SW_SPEED_CHANGE | LC_FORCE_DIS_HW_SPEED_CHANGE;
	speed_cntl &= ~LC_FORCE_DIS_SW_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	pci_read_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL2, &tmp16);
	tmp16 &= ~0xf;
	if (speed_cap == PCIE_SPEED_8_0GT)
		tmp16 |= 3; /* gen3 */
	else if (speed_cap == PCIE_SPEED_5_0GT)
		tmp16 |= 2; /* gen2 */
	else
		tmp16 |= 1; /* gen1 */
	pci_write_config_word(rdev->pdev, gpu_pos + PCI_EXP_LNKCTL2, tmp16);

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	speed_cntl |= LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	for (i = 0; i < rdev->usec_timeout; i++) {
		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		if ((speed_cntl & LC_INITIATE_LINK_SPEED_CHANGE) == 0)
			break;
		udelay(1);
	}
}