#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct list_head {int dummy; } ;
struct TYPE_15__ {int max_engine_clk_ccompute; int capability; int simd_count; int max_waves_per_simd; int /*<<< orphan*/  drm_render_minor; int /*<<< orphan*/  max_engine_clk_fcompute; int /*<<< orphan*/  location_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  simd_arrays_per_engine; } ;
struct kfd_topology_device {TYPE_7__ node_props; TYPE_6__* gpu; void* gpu_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  drm_render_minor; } ;
struct kfd_dev {TYPE_4__ shared_resources; TYPE_2__* pdev; void* id; } ;
struct kfd_cu_info {int simd_per_cu; int cu_active_number; int /*<<< orphan*/  num_shader_arrays_per_engine; } ;
struct TYPE_16__ {int /*<<< orphan*/  generation_count; } ;
struct TYPE_14__ {TYPE_5__* device_info; int /*<<< orphan*/  kgd; TYPE_3__* kfd2kgd; } ;
struct TYPE_13__ {int asic_family; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* get_max_engine_clock_in_mhz ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_cu_info ) (int /*<<< orphan*/ ,struct kfd_cu_info*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  devfn; TYPE_1__* bus; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct TYPE_9__ {int /*<<< orphan*/  number; } ;

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
 int /*<<< orphan*/  COMPUTE_UNIT_GPU ; 
 int ENODEV ; 
 int HSA_CAP_ATS_PRESENT ; 
 int HSA_CAP_DOORBELL_TYPE_1_0 ; 
 int HSA_CAP_DOORBELL_TYPE_2_0 ; 
 int HSA_CAP_DOORBELL_TYPE_PRE_1_0 ; 
 int HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK ; 
 int HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int cpufreq_quick_get_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct kfd_topology_device* kfd_assign_gpu (struct kfd_dev*) ; 
 int kfd_create_crat_image_virtual (void**,size_t*,int /*<<< orphan*/ ,struct kfd_dev*,int) ; 
 int /*<<< orphan*/  kfd_debug_print_topology () ; 
 int /*<<< orphan*/  kfd_destroy_crat_image (void*) ; 
 int /*<<< orphan*/  kfd_fill_iolink_non_crat_info (struct kfd_topology_device*) ; 
 int /*<<< orphan*/  kfd_fill_mem_clk_max_info (struct kfd_topology_device*) ; 
 void* kfd_generate_gpu_id (struct kfd_dev*) ; 
 int /*<<< orphan*/  kfd_notify_gpu_change (void*,int) ; 
 int kfd_parse_crat_table (void*,struct list_head*,int) ; 
 int /*<<< orphan*/  kfd_topology_update_device_list (struct list_head*,int /*<<< orphan*/ *) ; 
 int kfd_topology_update_sysfs () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,void*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct kfd_cu_info*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 TYPE_8__ sys_props ; 
 int /*<<< orphan*/  topology_crat_proximity_domain ; 
 int /*<<< orphan*/  topology_device_list ; 
 int /*<<< orphan*/  topology_lock ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int kfd_topology_add_device(struct kfd_dev *gpu)
{
	uint32_t gpu_id;
	struct kfd_topology_device *dev;
	struct kfd_cu_info cu_info;
	int res = 0;
	struct list_head temp_topology_device_list;
	void *crat_image = NULL;
	size_t image_size = 0;
	int proximity_domain;

	INIT_LIST_HEAD(&temp_topology_device_list);

	gpu_id = kfd_generate_gpu_id(gpu);

	pr_debug("Adding new GPU (ID: 0x%x) to topology\n", gpu_id);

	proximity_domain = atomic_inc_return(&topology_crat_proximity_domain);

	/* Check to see if this gpu device exists in the topology_device_list.
	 * If so, assign the gpu to that device,
	 * else create a Virtual CRAT for this gpu device and then parse that
	 * CRAT to create a new topology device. Once created assign the gpu to
	 * that topology device
	 */
	dev = kfd_assign_gpu(gpu);
	if (!dev) {
		res = kfd_create_crat_image_virtual(&crat_image, &image_size,
						    COMPUTE_UNIT_GPU, gpu,
						    proximity_domain);
		if (res) {
			pr_err("Error creating VCRAT for GPU (ID: 0x%x)\n",
			       gpu_id);
			return res;
		}
		res = kfd_parse_crat_table(crat_image,
					   &temp_topology_device_list,
					   proximity_domain);
		if (res) {
			pr_err("Error parsing VCRAT for GPU (ID: 0x%x)\n",
			       gpu_id);
			goto err;
		}

		down_write(&topology_lock);
		kfd_topology_update_device_list(&temp_topology_device_list,
			&topology_device_list);

		/* Update the SYSFS tree, since we added another topology
		 * device
		 */
		res = kfd_topology_update_sysfs();
		up_write(&topology_lock);

		if (!res)
			sys_props.generation_count++;
		else
			pr_err("Failed to update GPU (ID: 0x%x) to sysfs topology. res=%d\n",
						gpu_id, res);
		dev = kfd_assign_gpu(gpu);
		if (WARN_ON(!dev)) {
			res = -ENODEV;
			goto err;
		}
	}

	dev->gpu_id = gpu_id;
	gpu->id = gpu_id;

	/* TODO: Move the following lines to function
	 *	kfd_add_non_crat_information
	 */

	/* Fill-in additional information that is not available in CRAT but
	 * needed for the topology
	 */

	dev->gpu->kfd2kgd->get_cu_info(dev->gpu->kgd, &cu_info);
	dev->node_props.simd_arrays_per_engine =
		cu_info.num_shader_arrays_per_engine;

	dev->node_props.vendor_id = gpu->pdev->vendor;
	dev->node_props.device_id = gpu->pdev->device;
	dev->node_props.location_id = PCI_DEVID(gpu->pdev->bus->number,
		gpu->pdev->devfn);
	dev->node_props.max_engine_clk_fcompute =
		dev->gpu->kfd2kgd->get_max_engine_clock_in_mhz(dev->gpu->kgd);
	dev->node_props.max_engine_clk_ccompute =
		cpufreq_quick_get_max(0) / 1000;
	dev->node_props.drm_render_minor =
		gpu->shared_resources.drm_render_minor;

	kfd_fill_mem_clk_max_info(dev);
	kfd_fill_iolink_non_crat_info(dev);

	switch (dev->gpu->device_info->asic_family) {
	case CHIP_KAVERI:
	case CHIP_HAWAII:
	case CHIP_TONGA:
		dev->node_props.capability |= ((HSA_CAP_DOORBELL_TYPE_PRE_1_0 <<
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT) &
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK);
		break;
	case CHIP_CARRIZO:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
		pr_debug("Adding doorbell packet type capability\n");
		dev->node_props.capability |= ((HSA_CAP_DOORBELL_TYPE_1_0 <<
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT) &
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK);
		break;
	case CHIP_VEGA10:
	case CHIP_RAVEN:
		dev->node_props.capability |= ((HSA_CAP_DOORBELL_TYPE_2_0 <<
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT) &
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK);
		break;
	default:
		WARN(1, "Unexpected ASIC family %u",
		     dev->gpu->device_info->asic_family);
	}

	/* Fix errors in CZ CRAT.
	 * simd_count: Carrizo CRAT reports wrong simd_count, probably
	 *		because it doesn't consider masked out CUs
	 * max_waves_per_simd: Carrizo reports wrong max_waves_per_simd
	 * capability flag: Carrizo CRAT doesn't report IOMMU flags
	 */
	if (dev->gpu->device_info->asic_family == CHIP_CARRIZO) {
		dev->node_props.simd_count =
			cu_info.simd_per_cu * cu_info.cu_active_number;
		dev->node_props.max_waves_per_simd = 10;
		dev->node_props.capability |= HSA_CAP_ATS_PRESENT;
	}

	kfd_debug_print_topology();

	if (!res)
		kfd_notify_gpu_change(gpu_id, 1);
err:
	kfd_destroy_crat_image(crat_image);
	return res;
}