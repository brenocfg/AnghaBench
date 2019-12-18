#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  ib_base; int /*<<< orphan*/  cwsr_base; } ;
struct kfd_process_device {scalar_t__ scratch_limit; scalar_t__ scratch_base; scalar_t__ gpuvm_limit; scalar_t__ gpuvm_base; scalar_t__ lds_limit; scalar_t__ lds_base; TYPE_3__* dev; TYPE_2__ qpd; } ;
struct kfd_process {scalar_t__ is_32bit_user_mode; } ;
struct kfd_dev {TYPE_1__* device_info; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_4__ {int asic_family; int /*<<< orphan*/  needs_iommu_device; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 142 
#define  CHIP_CARRIZO 141 
#define  CHIP_FIJI 140 
#define  CHIP_HAWAII 139 
#define  CHIP_KAVERI 138 
#define  CHIP_NAVI10 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_POLARIS12 134 
#define  CHIP_RAVEN 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SVM_CWSR_BASE ; 
 int /*<<< orphan*/  SVM_IB_BASE ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct kfd_process_device* kfd_create_process_device_data (struct kfd_dev*,struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_device ; 
 int /*<<< orphan*/  kfd_init_apertures_v9 (struct kfd_process_device*,scalar_t__) ; 
 int /*<<< orphan*/  kfd_init_apertures_vi (struct kfd_process_device*,scalar_t__) ; 
 scalar_t__ kfd_topology_enum_kfd_devices (scalar_t__,struct kfd_dev**) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int kfd_init_apertures(struct kfd_process *process)
{
	uint8_t id  = 0;
	struct kfd_dev *dev;
	struct kfd_process_device *pdd;

	/*Iterating over all devices*/
	while (kfd_topology_enum_kfd_devices(id, &dev) == 0) {
		if (!dev) {
			id++; /* Skip non GPU devices */
			continue;
		}

		pdd = kfd_create_process_device_data(dev, process);
		if (!pdd) {
			pr_err("Failed to create process device data\n");
			return -ENOMEM;
		}
		/*
		 * For 64 bit process apertures will be statically reserved in
		 * the x86_64 non canonical process address space
		 * amdkfd doesn't currently support apertures for 32 bit process
		 */
		if (process->is_32bit_user_mode) {
			pdd->lds_base = pdd->lds_limit = 0;
			pdd->gpuvm_base = pdd->gpuvm_limit = 0;
			pdd->scratch_base = pdd->scratch_limit = 0;
		} else {
			switch (dev->device_info->asic_family) {
			case CHIP_KAVERI:
			case CHIP_HAWAII:
			case CHIP_CARRIZO:
			case CHIP_TONGA:
			case CHIP_FIJI:
			case CHIP_POLARIS10:
			case CHIP_POLARIS11:
			case CHIP_POLARIS12:
			case CHIP_VEGAM:
				kfd_init_apertures_vi(pdd, id);
				break;
			case CHIP_VEGA10:
			case CHIP_VEGA12:
			case CHIP_VEGA20:
			case CHIP_RAVEN:
			case CHIP_ARCTURUS:
			case CHIP_NAVI10:
				kfd_init_apertures_v9(pdd, id);
				break;
			default:
				WARN(1, "Unexpected ASIC family %u",
				     dev->device_info->asic_family);
				return -EINVAL;
			}

			if (!dev->device_info->needs_iommu_device) {
				/* dGPUs: the reserved space for kernel
				 * before SVM
				 */
				pdd->qpd.cwsr_base = SVM_CWSR_BASE;
				pdd->qpd.ib_base = SVM_IB_BASE;
			}
		}

		dev_dbg(kfd_device, "node id %u\n", id);
		dev_dbg(kfd_device, "gpu id %u\n", pdd->dev->id);
		dev_dbg(kfd_device, "lds_base %llX\n", pdd->lds_base);
		dev_dbg(kfd_device, "lds_limit %llX\n", pdd->lds_limit);
		dev_dbg(kfd_device, "gpuvm_base %llX\n", pdd->gpuvm_base);
		dev_dbg(kfd_device, "gpuvm_limit %llX\n", pdd->gpuvm_limit);
		dev_dbg(kfd_device, "scratch_base %llX\n", pdd->scratch_base);
		dev_dbg(kfd_device, "scratch_limit %llX\n", pdd->scratch_limit);

		id++;
	}

	return 0;
}