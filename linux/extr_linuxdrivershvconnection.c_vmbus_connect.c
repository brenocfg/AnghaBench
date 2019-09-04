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
struct vmbus_channel_msginfo {int dummy; } ;
struct vmbus_channel_initiate_contact {int dummy; } ;
typedef  int __u32 ;
struct TYPE_2__ {scalar_t__ conn_state; int /*<<< orphan*/ ** monitor_pages; int /*<<< orphan*/ * int_page; void* send_int_page; int /*<<< orphan*/ * recv_int_page; int /*<<< orphan*/  channel_mutex; int /*<<< orphan*/  chn_list; int /*<<< orphan*/  channelmsg_lock; int /*<<< orphan*/  chn_msg_list; void* handle_sub_chan_wq; void* handle_primary_chan_wq; void* work_queue; } ;

/* Variables and functions */
 scalar_t__ CONNECTED ; 
 scalar_t__ CONNECTING ; 
 scalar_t__ DISCONNECTED ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int VERSION_CURRENT ; 
 int VERSION_INVAL ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 void* create_workqueue (char*) ; 
 int /*<<< orphan*/  kfree (struct vmbus_channel_msginfo*) ; 
 struct vmbus_channel_msginfo* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_disconnect () ; 
 int vmbus_get_next_version (int) ; 
 int vmbus_negotiate_version (struct vmbus_channel_msginfo*,int) ; 
 int vmbus_proto_version ; 

int vmbus_connect(void)
{
	int ret = 0;
	struct vmbus_channel_msginfo *msginfo = NULL;
	__u32 version;

	/* Initialize the vmbus connection */
	vmbus_connection.conn_state = CONNECTING;
	vmbus_connection.work_queue = create_workqueue("hv_vmbus_con");
	if (!vmbus_connection.work_queue) {
		ret = -ENOMEM;
		goto cleanup;
	}

	vmbus_connection.handle_primary_chan_wq =
		create_workqueue("hv_pri_chan");
	if (!vmbus_connection.handle_primary_chan_wq) {
		ret = -ENOMEM;
		goto cleanup;
	}

	vmbus_connection.handle_sub_chan_wq =
		create_workqueue("hv_sub_chan");
	if (!vmbus_connection.handle_sub_chan_wq) {
		ret = -ENOMEM;
		goto cleanup;
	}

	INIT_LIST_HEAD(&vmbus_connection.chn_msg_list);
	spin_lock_init(&vmbus_connection.channelmsg_lock);

	INIT_LIST_HEAD(&vmbus_connection.chn_list);
	mutex_init(&vmbus_connection.channel_mutex);

	/*
	 * Setup the vmbus event connection for channel interrupt
	 * abstraction stuff
	 */
	vmbus_connection.int_page =
	(void *)__get_free_pages(GFP_KERNEL|__GFP_ZERO, 0);
	if (vmbus_connection.int_page == NULL) {
		ret = -ENOMEM;
		goto cleanup;
	}

	vmbus_connection.recv_int_page = vmbus_connection.int_page;
	vmbus_connection.send_int_page =
		(void *)((unsigned long)vmbus_connection.int_page +
			(PAGE_SIZE >> 1));

	/*
	 * Setup the monitor notification facility. The 1st page for
	 * parent->child and the 2nd page for child->parent
	 */
	vmbus_connection.monitor_pages[0] = (void *)__get_free_pages((GFP_KERNEL|__GFP_ZERO), 0);
	vmbus_connection.monitor_pages[1] = (void *)__get_free_pages((GFP_KERNEL|__GFP_ZERO), 0);
	if ((vmbus_connection.monitor_pages[0] == NULL) ||
	    (vmbus_connection.monitor_pages[1] == NULL)) {
		ret = -ENOMEM;
		goto cleanup;
	}

	msginfo = kzalloc(sizeof(*msginfo) +
			  sizeof(struct vmbus_channel_initiate_contact),
			  GFP_KERNEL);
	if (msginfo == NULL) {
		ret = -ENOMEM;
		goto cleanup;
	}

	/*
	 * Negotiate a compatible VMBUS version number with the
	 * host. We start with the highest number we can support
	 * and work our way down until we negotiate a compatible
	 * version.
	 */

	version = VERSION_CURRENT;

	do {
		ret = vmbus_negotiate_version(msginfo, version);
		if (ret == -ETIMEDOUT)
			goto cleanup;

		if (vmbus_connection.conn_state == CONNECTED)
			break;

		version = vmbus_get_next_version(version);
	} while (version != VERSION_INVAL);

	if (version == VERSION_INVAL)
		goto cleanup;

	vmbus_proto_version = version;
	pr_info("Vmbus version:%d.%d\n",
		version >> 16, version & 0xFFFF);

	kfree(msginfo);
	return 0;

cleanup:
	pr_err("Unable to connect to host\n");

	vmbus_connection.conn_state = DISCONNECTED;
	vmbus_disconnect();

	kfree(msginfo);

	return ret;
}