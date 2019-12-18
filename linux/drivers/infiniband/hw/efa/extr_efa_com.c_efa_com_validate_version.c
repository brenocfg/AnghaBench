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
struct efa_com_dev {int /*<<< orphan*/  efa_dev; } ;

/* Variables and functions */
 int EFA_REGS_CONTROLLER_VERSION_IMPL_ID_MASK ; 
 int EFA_REGS_CONTROLLER_VERSION_IMPL_ID_SHIFT ; 
 int EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK ; 
 int EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_SHIFT ; 
 int EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK ; 
 int EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION_SHIFT ; 
 int /*<<< orphan*/  EFA_REGS_CONTROLLER_VERSION_OFF ; 
 int EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK ; 
 int EFA_REGS_VERSION_MAJOR_VERSION_MASK ; 
 int EFA_REGS_VERSION_MAJOR_VERSION_SHIFT ; 
 int EFA_REGS_VERSION_MINOR_VERSION_MASK ; 
 int /*<<< orphan*/  EFA_REGS_VERSION_OFF ; 
 int EOPNOTSUPP ; 
 int MIN_EFA_CTRL_VER ; 
 int MIN_EFA_VER ; 
 int efa_com_reg_read32 (struct efa_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ ,char*) ; 

int efa_com_validate_version(struct efa_com_dev *edev)
{
	u32 ctrl_ver_masked;
	u32 ctrl_ver;
	u32 ver;

	/*
	 * Make sure the EFA version and the controller version are at least
	 * as the driver expects
	 */
	ver = efa_com_reg_read32(edev, EFA_REGS_VERSION_OFF);
	ctrl_ver = efa_com_reg_read32(edev,
				      EFA_REGS_CONTROLLER_VERSION_OFF);

	ibdev_dbg(edev->efa_dev, "efa device version: %d.%d\n",
		  (ver & EFA_REGS_VERSION_MAJOR_VERSION_MASK) >>
			  EFA_REGS_VERSION_MAJOR_VERSION_SHIFT,
		  ver & EFA_REGS_VERSION_MINOR_VERSION_MASK);

	if (ver < MIN_EFA_VER) {
		ibdev_err(edev->efa_dev,
			  "EFA version is lower than the minimal version the driver supports\n");
		return -EOPNOTSUPP;
	}

	ibdev_dbg(edev->efa_dev,
		  "efa controller version: %d.%d.%d implementation version %d\n",
		  (ctrl_ver & EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK) >>
			  EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_SHIFT,
		  (ctrl_ver & EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK) >>
			  EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION_SHIFT,
		  (ctrl_ver & EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK),
		  (ctrl_ver & EFA_REGS_CONTROLLER_VERSION_IMPL_ID_MASK) >>
			  EFA_REGS_CONTROLLER_VERSION_IMPL_ID_SHIFT);

	ctrl_ver_masked =
		(ctrl_ver & EFA_REGS_CONTROLLER_VERSION_MAJOR_VERSION_MASK) |
		(ctrl_ver & EFA_REGS_CONTROLLER_VERSION_MINOR_VERSION_MASK) |
		(ctrl_ver & EFA_REGS_CONTROLLER_VERSION_SUBMINOR_VERSION_MASK);

	/* Validate the ctrl version without the implementation ID */
	if (ctrl_ver_masked < MIN_EFA_CTRL_VER) {
		ibdev_err(edev->efa_dev,
			  "EFA ctrl version is lower than the minimal ctrl version the driver supports\n");
		return -EOPNOTSUPP;
	}

	return 0;
}