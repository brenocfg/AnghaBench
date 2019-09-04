#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct hid_device {int /*<<< orphan*/  ll_open_lock; int /*<<< orphan*/  driver_input_lock; int /*<<< orphan*/  debug_list_lock; int /*<<< orphan*/  debug_list; int /*<<< orphan*/  debug_wait; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hid_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_enable_async_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  hid_bus_type ; 
 int /*<<< orphan*/  hid_close_report (struct hid_device*) ; 
 int /*<<< orphan*/  hid_device_release ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct hid_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct hid_device *hid_allocate_device(void)
{
	struct hid_device *hdev;
	int ret = -ENOMEM;

	hdev = kzalloc(sizeof(*hdev), GFP_KERNEL);
	if (hdev == NULL)
		return ERR_PTR(ret);

	device_initialize(&hdev->dev);
	hdev->dev.release = hid_device_release;
	hdev->dev.bus = &hid_bus_type;
	device_enable_async_suspend(&hdev->dev);

	hid_close_report(hdev);

	init_waitqueue_head(&hdev->debug_wait);
	INIT_LIST_HEAD(&hdev->debug_list);
	spin_lock_init(&hdev->debug_list_lock);
	sema_init(&hdev->driver_input_lock, 1);
	mutex_init(&hdev->ll_open_lock);

	return hdev;
}