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
struct device_queue_manager {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_3__ {int (* set_pasid_vmid_mapping ) (int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int
set_pasid_vmid_mapping(struct device_queue_manager *dqm, unsigned int pasid,
			unsigned int vmid)
{
	return dqm->dev->kfd2kgd->set_pasid_vmid_mapping(
						dqm->dev->kgd, pasid, vmid);
}