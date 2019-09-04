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
struct kfd_dev {int dummy; } ;
struct kfd_dbgdev {int type; int /*<<< orphan*/  dbgdev_address_watch; int /*<<< orphan*/  dbgdev_wave_control; int /*<<< orphan*/  dbgdev_unregister; int /*<<< orphan*/  dbgdev_register; int /*<<< orphan*/ * pqm; int /*<<< orphan*/ * kq; struct kfd_dev* dev; } ;
typedef  enum DBGDEV_TYPE { ____Placeholder_DBGDEV_TYPE } DBGDEV_TYPE ;

/* Variables and functions */
#define  DBGDEV_TYPE_DIQ 129 
#define  DBGDEV_TYPE_NODIQ 128 
 int /*<<< orphan*/  dbgdev_address_watch_diq ; 
 int /*<<< orphan*/  dbgdev_address_watch_nodiq ; 
 int /*<<< orphan*/  dbgdev_register_diq ; 
 int /*<<< orphan*/  dbgdev_register_nodiq ; 
 int /*<<< orphan*/  dbgdev_unregister_diq ; 
 int /*<<< orphan*/  dbgdev_unregister_nodiq ; 
 int /*<<< orphan*/  dbgdev_wave_control_diq ; 
 int /*<<< orphan*/  dbgdev_wave_control_nodiq ; 

void kfd_dbgdev_init(struct kfd_dbgdev *pdbgdev, struct kfd_dev *pdev,
			enum DBGDEV_TYPE type)
{
	pdbgdev->dev = pdev;
	pdbgdev->kq = NULL;
	pdbgdev->type = type;
	pdbgdev->pqm = NULL;

	switch (type) {
	case DBGDEV_TYPE_NODIQ:
		pdbgdev->dbgdev_register = dbgdev_register_nodiq;
		pdbgdev->dbgdev_unregister = dbgdev_unregister_nodiq;
		pdbgdev->dbgdev_wave_control = dbgdev_wave_control_nodiq;
		pdbgdev->dbgdev_address_watch = dbgdev_address_watch_nodiq;
		break;
	case DBGDEV_TYPE_DIQ:
	default:
		pdbgdev->dbgdev_register = dbgdev_register_diq;
		pdbgdev->dbgdev_unregister = dbgdev_unregister_diq;
		pdbgdev->dbgdev_wave_control =  dbgdev_wave_control_diq;
		pdbgdev->dbgdev_address_watch = dbgdev_address_watch_diq;
		break;
	}

}