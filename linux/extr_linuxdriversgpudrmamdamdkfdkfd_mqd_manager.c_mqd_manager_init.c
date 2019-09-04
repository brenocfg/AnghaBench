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
struct mqd_manager {int dummy; } ;
struct kfd_dev {TYPE_1__* device_info; } ;
typedef  enum KFD_MQD_TYPE { ____Placeholder_KFD_MQD_TYPE } KFD_MQD_TYPE ;
struct TYPE_2__ {int asic_family; } ;

/* Variables and functions */
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_HAWAII 134 
#define  CHIP_KAVERI 133 
#define  CHIP_POLARIS10 132 
#define  CHIP_POLARIS11 131 
#define  CHIP_RAVEN 130 
#define  CHIP_TONGA 129 
#define  CHIP_VEGA10 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 struct mqd_manager* mqd_manager_init_cik (int,struct kfd_dev*) ; 
 struct mqd_manager* mqd_manager_init_cik_hawaii (int,struct kfd_dev*) ; 
 struct mqd_manager* mqd_manager_init_v9 (int,struct kfd_dev*) ; 
 struct mqd_manager* mqd_manager_init_vi (int,struct kfd_dev*) ; 
 struct mqd_manager* mqd_manager_init_vi_tonga (int,struct kfd_dev*) ; 

struct mqd_manager *mqd_manager_init(enum KFD_MQD_TYPE type,
					struct kfd_dev *dev)
{
	switch (dev->device_info->asic_family) {
	case CHIP_KAVERI:
		return mqd_manager_init_cik(type, dev);
	case CHIP_HAWAII:
		return mqd_manager_init_cik_hawaii(type, dev);
	case CHIP_CARRIZO:
		return mqd_manager_init_vi(type, dev);
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
		return mqd_manager_init_vi_tonga(type, dev);
	case CHIP_VEGA10:
	case CHIP_RAVEN:
		return mqd_manager_init_v9(type, dev);
	default:
		WARN(1, "Unexpected ASIC family %u",
		     dev->device_info->asic_family);
	}

	return NULL;
}