#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hv_vmbus_device_id {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {int /*<<< orphan*/  wrk; } ;
struct TYPE_6__ {int /*<<< orphan*/  wrk; } ;
struct TYPE_8__ {int host_specified_ha_region; int /*<<< orphan*/  thread; int /*<<< orphan*/  state; TYPE_2__ ha_wrk; TYPE_1__ balloon_wrk; int /*<<< orphan*/  ha_lock; int /*<<< orphan*/  ha_region_list; int /*<<< orphan*/  config_event; int /*<<< orphan*/  host_event; int /*<<< orphan*/  next_version; struct hv_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_INITIALIZED ; 
 int /*<<< orphan*/  DM_INITIALIZING ; 
 int /*<<< orphan*/  DYNMEM_PROTOCOL_VERSION_WIN8 ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int balloon_connect_vsp (struct hv_device*) ; 
 int /*<<< orphan*/  balloon_up ; 
 TYPE_3__ dm_device ; 
 int /*<<< orphan*/  dm_thread_func ; 
 int do_hot_add ; 
 int hot_add ; 
 int /*<<< orphan*/  hot_add_req ; 
 int /*<<< orphan*/  hv_memory_nb ; 
 int /*<<< orphan*/  hv_online_page ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  register_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_online_page_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_online_page_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int balloon_probe(struct hv_device *dev,
			 const struct hv_vmbus_device_id *dev_id)
{
	int ret;

#ifdef CONFIG_MEMORY_HOTPLUG
	do_hot_add = hot_add;
#else
	do_hot_add = false;
#endif
	dm_device.dev = dev;
	dm_device.state = DM_INITIALIZING;
	dm_device.next_version = DYNMEM_PROTOCOL_VERSION_WIN8;
	init_completion(&dm_device.host_event);
	init_completion(&dm_device.config_event);
	INIT_LIST_HEAD(&dm_device.ha_region_list);
	spin_lock_init(&dm_device.ha_lock);
	INIT_WORK(&dm_device.balloon_wrk.wrk, balloon_up);
	INIT_WORK(&dm_device.ha_wrk.wrk, hot_add_req);
	dm_device.host_specified_ha_region = false;

#ifdef CONFIG_MEMORY_HOTPLUG
	set_online_page_callback(&hv_online_page);
	register_memory_notifier(&hv_memory_nb);
#endif

	hv_set_drvdata(dev, &dm_device);

	ret = balloon_connect_vsp(dev);
	if (ret != 0)
		return ret;

	dm_device.state = DM_INITIALIZED;

	dm_device.thread =
		 kthread_run(dm_thread_func, &dm_device, "hv_balloon");
	if (IS_ERR(dm_device.thread)) {
		ret = PTR_ERR(dm_device.thread);
		goto probe_error;
	}

	return 0;

probe_error:
	vmbus_close(dev->channel);
#ifdef CONFIG_MEMORY_HOTPLUG
	unregister_memory_notifier(&hv_memory_nb);
	restore_online_page_callback(&hv_online_page);
#endif
	return ret;
}