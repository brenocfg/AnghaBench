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
typedef  int u32 ;
struct ena_com_dev {int dummy; } ;

/* Variables and functions */
 int ENA_MMIO_READ_TIMEOUT ; 
 int ENA_REGS_CONTROLLER_VERSION_IMPL_ID_MASK ; 
 int ENA_REGS_CONTROLLER_VERSION_IMPL_ID_SHIFT ; 
 int ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK ; 
 int ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_SHIFT ; 
 int ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK ; 
 int ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_SHIFT ; 
 int /*<<< orphan*/  ENA_REGS_CONTROLLER_VERSION_OFF ; 
 int ENA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK ; 
 int ENA_REGS_VERSION_MAJOR_VERSION_MASK ; 
 int ENA_REGS_VERSION_MAJOR_VERSION_SHIFT ; 
 int ENA_REGS_VERSION_MINOR_VERSION_MASK ; 
 int /*<<< orphan*/  ENA_REGS_VERSION_OFF ; 
 int ETIME ; 
 int MIN_ENA_CTRL_VER ; 
 int ena_com_reg_bar_read32 (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_validate_version(struct ena_com_dev *ena_dev)
{
	u32 ver;
	u32 ctrl_ver;
	u32 ctrl_ver_masked;

	/* Make sure the ENA version and the controller version are at least
	 * as the driver expects
	 */
	ver = ena_com_reg_bar_read32(ena_dev, ENA_REGS_VERSION_OFF);
	ctrl_ver = ena_com_reg_bar_read32(ena_dev,
					  ENA_REGS_CONTROLLER_VERSION_OFF);

	if (unlikely((ver == ENA_MMIO_READ_TIMEOUT) ||
		     (ctrl_ver == ENA_MMIO_READ_TIMEOUT))) {
		pr_err("Reg read timeout occurred\n");
		return -ETIME;
	}

	pr_info("ena device version: %d.%d\n",
		(ver & ENA_REGS_VERSION_MAJOR_VERSION_MASK) >>
			ENA_REGS_VERSION_MAJOR_VERSION_SHIFT,
		ver & ENA_REGS_VERSION_MINOR_VERSION_MASK);

	pr_info("ena controller version: %d.%d.%d implementation version %d\n",
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK) >>
			ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_SHIFT,
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK) >>
			ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_SHIFT,
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK),
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_IMPL_ID_MASK) >>
			ENA_REGS_CONTROLLER_VERSION_IMPL_ID_SHIFT);

	ctrl_ver_masked =
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK) |
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK) |
		(ctrl_ver & ENA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK);

	/* Validate the ctrl version without the implementation ID */
	if (ctrl_ver_masked < MIN_ENA_CTRL_VER) {
		pr_err("ENA ctrl version is lower than the minimal ctrl version the driver supports\n");
		return -1;
	}

	return 0;
}