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
struct TYPE_2__ {int state; } ;
struct nvme_dev {TYPE_1__ ctrl; scalar_t__ subsystem; } ;

/* Variables and functions */
 int NVME_CSTS_CFS ; 
 int NVME_CSTS_NSSRO ; 
#define  NVME_CTRL_CONNECTING 129 
#define  NVME_CTRL_RESETTING 128 

__attribute__((used)) static bool nvme_should_reset(struct nvme_dev *dev, u32 csts)
{

	/* If true, indicates loss of adapter communication, possibly by a
	 * NVMe Subsystem reset.
	 */
	bool nssro = dev->subsystem && (csts & NVME_CSTS_NSSRO);

	/* If there is a reset/reinit ongoing, we shouldn't reset again. */
	switch (dev->ctrl.state) {
	case NVME_CTRL_RESETTING:
	case NVME_CTRL_CONNECTING:
		return false;
	default:
		break;
	}

	/* We shouldn't reset unless the controller is on fatal error state
	 * _or_ if we lost the communication with it.
	 */
	if (!(csts & NVME_CSTS_CFS) && !nssro)
		return false;

	return true;
}