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
struct hwmon_chip_info {int dummy; } ;
struct hl_device_idle_busy_ts {int dummy; } ;
struct hl_device {int asic_type; TYPE_1__* asic_funcs; int /*<<< orphan*/ * cq_wq; int /*<<< orphan*/ * eq_wq; int /*<<< orphan*/  hl_chip_info; int /*<<< orphan*/  in_reset; int /*<<< orphan*/  fpriv_list_lock; int /*<<< orphan*/  fpriv_list; int /*<<< orphan*/  hw_queues_mirror_lock; int /*<<< orphan*/  hw_queues_mirror_list; int /*<<< orphan*/  mmu_cache_lock; int /*<<< orphan*/  debug_lock; int /*<<< orphan*/  send_cpu_message_lock; int /*<<< orphan*/  kernel_cb_mgr; int /*<<< orphan*/  idle_busy_ts_arr; int /*<<< orphan*/  dev; int /*<<< orphan*/  asic_name; } ;
struct TYPE_2__ {int (* early_init ) (struct hl_device*) ;int /*<<< orphan*/  (* early_fini ) (struct hl_device*) ;} ;

/* Variables and functions */
#define  ASIC_GOYA 128 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  HL_IDLE_BUSY_TS_ARR_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int __GFP_ZERO ; 
 void* alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  goya_set_asic_funcs (struct hl_device*) ; 
 int /*<<< orphan*/  hl_asid_fini (struct hl_device*) ; 
 int hl_asid_init (struct hl_device*) ; 
 int /*<<< orphan*/  hl_cb_mgr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_array (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct hl_device*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*) ; 

__attribute__((used)) static int device_early_init(struct hl_device *hdev)
{
	int rc;

	switch (hdev->asic_type) {
	case ASIC_GOYA:
		goya_set_asic_funcs(hdev);
		strlcpy(hdev->asic_name, "GOYA", sizeof(hdev->asic_name));
		break;
	default:
		dev_err(hdev->dev, "Unrecognized ASIC type %d\n",
			hdev->asic_type);
		return -EINVAL;
	}

	rc = hdev->asic_funcs->early_init(hdev);
	if (rc)
		return rc;

	rc = hl_asid_init(hdev);
	if (rc)
		goto early_fini;

	hdev->cq_wq = alloc_workqueue("hl-free-jobs", WQ_UNBOUND, 0);
	if (hdev->cq_wq == NULL) {
		dev_err(hdev->dev, "Failed to allocate CQ workqueue\n");
		rc = -ENOMEM;
		goto asid_fini;
	}

	hdev->eq_wq = alloc_workqueue("hl-events", WQ_UNBOUND, 0);
	if (hdev->eq_wq == NULL) {
		dev_err(hdev->dev, "Failed to allocate EQ workqueue\n");
		rc = -ENOMEM;
		goto free_cq_wq;
	}

	hdev->hl_chip_info = kzalloc(sizeof(struct hwmon_chip_info),
					GFP_KERNEL);
	if (!hdev->hl_chip_info) {
		rc = -ENOMEM;
		goto free_eq_wq;
	}

	hdev->idle_busy_ts_arr = kmalloc_array(HL_IDLE_BUSY_TS_ARR_SIZE,
					sizeof(struct hl_device_idle_busy_ts),
					(GFP_KERNEL | __GFP_ZERO));
	if (!hdev->idle_busy_ts_arr) {
		rc = -ENOMEM;
		goto free_chip_info;
	}

	hl_cb_mgr_init(&hdev->kernel_cb_mgr);

	mutex_init(&hdev->send_cpu_message_lock);
	mutex_init(&hdev->debug_lock);
	mutex_init(&hdev->mmu_cache_lock);
	INIT_LIST_HEAD(&hdev->hw_queues_mirror_list);
	spin_lock_init(&hdev->hw_queues_mirror_lock);
	INIT_LIST_HEAD(&hdev->fpriv_list);
	mutex_init(&hdev->fpriv_list_lock);
	atomic_set(&hdev->in_reset, 0);

	return 0;

free_chip_info:
	kfree(hdev->hl_chip_info);
free_eq_wq:
	destroy_workqueue(hdev->eq_wq);
free_cq_wq:
	destroy_workqueue(hdev->cq_wq);
asid_fini:
	hl_asid_fini(hdev);
early_fini:
	if (hdev->asic_funcs->early_fini)
		hdev->asic_funcs->early_fini(hdev);

	return rc;
}