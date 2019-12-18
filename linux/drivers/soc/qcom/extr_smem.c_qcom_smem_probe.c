#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct smem_region {int dummy; } ;
struct smem_header {int /*<<< orphan*/  reserved; int /*<<< orphan*/  initialized; } ;
struct qcom_smem {int num_regions; int /*<<< orphan*/  socinfo; int /*<<< orphan*/  hwlock; int /*<<< orphan*/  item_count; TYPE_1__* regions; TYPE_2__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {struct smem_header* virt_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
#define  SMEM_GLOBAL_HEAP_VERSION 129 
#define  SMEM_GLOBAL_PART_VERSION 128 
 scalar_t__ SMEM_HOST_APPS ; 
 scalar_t__ SMEM_HOST_COUNT ; 
 int /*<<< orphan*/  SMEM_ITEM_COUNT ; 
 struct qcom_smem* __smem ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct qcom_smem* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwspin_lock_request_specific (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int of_hwspin_lock_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_register_data (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qcom_smem_enumerate_partitions (struct qcom_smem*,scalar_t__) ; 
 int /*<<< orphan*/  qcom_smem_get_item_count (struct qcom_smem*) ; 
 int qcom_smem_get_sbl_version (struct qcom_smem*) ; 
 int qcom_smem_map_memory (struct qcom_smem*,TYPE_2__*,char*,int) ; 
 int qcom_smem_set_global_partition (struct qcom_smem*) ; 

__attribute__((used)) static int qcom_smem_probe(struct platform_device *pdev)
{
	struct smem_header *header;
	struct qcom_smem *smem;
	size_t array_size;
	int num_regions;
	int hwlock_id;
	u32 version;
	int ret;

	num_regions = 1;
	if (of_find_property(pdev->dev.of_node, "qcom,rpm-msg-ram", NULL))
		num_regions++;

	array_size = num_regions * sizeof(struct smem_region);
	smem = devm_kzalloc(&pdev->dev, sizeof(*smem) + array_size, GFP_KERNEL);
	if (!smem)
		return -ENOMEM;

	smem->dev = &pdev->dev;
	smem->num_regions = num_regions;

	ret = qcom_smem_map_memory(smem, &pdev->dev, "memory-region", 0);
	if (ret)
		return ret;

	if (num_regions > 1 && (ret = qcom_smem_map_memory(smem, &pdev->dev,
					"qcom,rpm-msg-ram", 1)))
		return ret;

	header = smem->regions[0].virt_base;
	if (le32_to_cpu(header->initialized) != 1 ||
	    le32_to_cpu(header->reserved)) {
		dev_err(&pdev->dev, "SMEM is not initialized by SBL\n");
		return -EINVAL;
	}

	version = qcom_smem_get_sbl_version(smem);
	switch (version >> 16) {
	case SMEM_GLOBAL_PART_VERSION:
		ret = qcom_smem_set_global_partition(smem);
		if (ret < 0)
			return ret;
		smem->item_count = qcom_smem_get_item_count(smem);
		break;
	case SMEM_GLOBAL_HEAP_VERSION:
		smem->item_count = SMEM_ITEM_COUNT;
		break;
	default:
		dev_err(&pdev->dev, "Unsupported SMEM version 0x%x\n", version);
		return -EINVAL;
	}

	BUILD_BUG_ON(SMEM_HOST_APPS >= SMEM_HOST_COUNT);
	ret = qcom_smem_enumerate_partitions(smem, SMEM_HOST_APPS);
	if (ret < 0 && ret != -ENOENT)
		return ret;

	hwlock_id = of_hwspin_lock_get_id(pdev->dev.of_node, 0);
	if (hwlock_id < 0) {
		if (hwlock_id != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to retrieve hwlock\n");
		return hwlock_id;
	}

	smem->hwlock = hwspin_lock_request_specific(hwlock_id);
	if (!smem->hwlock)
		return -ENXIO;

	__smem = smem;

	smem->socinfo = platform_device_register_data(&pdev->dev, "qcom-socinfo",
						      PLATFORM_DEVID_NONE, NULL,
						      0);
	if (IS_ERR(smem->socinfo))
		dev_dbg(&pdev->dev, "failed to register socinfo device\n");

	return 0;
}