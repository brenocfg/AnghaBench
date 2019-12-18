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
struct TYPE_2__ {int cb_pool_cb_cnt; int /*<<< orphan*/  cb_pool_cb_size; } ;
struct hl_device {int /*<<< orphan*/  cb_pool; TYPE_1__ asic_prop; int /*<<< orphan*/  cb_pool_lock; } ;
struct hl_cb {int is_pool; int /*<<< orphan*/  pool_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HL_KERNEL_ASID_ID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct hl_cb* hl_cb_alloc (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_cb_pool_fini (struct hl_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hl_cb_pool_init(struct hl_device *hdev)
{
	struct hl_cb *cb;
	int i;

	INIT_LIST_HEAD(&hdev->cb_pool);
	spin_lock_init(&hdev->cb_pool_lock);

	for (i = 0 ; i < hdev->asic_prop.cb_pool_cb_cnt ; i++) {
		cb = hl_cb_alloc(hdev, hdev->asic_prop.cb_pool_cb_size,
				HL_KERNEL_ASID_ID);
		if (cb) {
			cb->is_pool = true;
			list_add(&cb->pool_list, &hdev->cb_pool);
		} else {
			hl_cb_pool_fini(hdev);
			return -ENOMEM;
		}
	}

	return 0;
}