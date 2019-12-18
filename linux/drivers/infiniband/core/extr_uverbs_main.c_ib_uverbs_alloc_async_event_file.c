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
struct ib_uverbs_file {int /*<<< orphan*/  ref; int /*<<< orphan*/  event_handler; struct ib_uverbs_async_event_file* async_file; TYPE_1__* device; } ;
struct ib_uverbs_async_event_file {int /*<<< orphan*/  ref; struct ib_uverbs_file* uverbs_file; int /*<<< orphan*/  list; int /*<<< orphan*/  ev_queue; } ;
struct ib_device {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lists_mutex; int /*<<< orphan*/  uverbs_events_file_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  WARN_ON (struct ib_uverbs_async_event_file*) ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct ib_uverbs_async_event_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_uverbs_event_handler ; 
 int /*<<< orphan*/  ib_uverbs_init_event_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_uverbs_release_async_event_file ; 
 int /*<<< orphan*/  ib_uverbs_release_file ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_uverbs_async_event_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_async_event_fops ; 

struct file *ib_uverbs_alloc_async_event_file(struct ib_uverbs_file *uverbs_file,
					      struct ib_device	*ib_dev)
{
	struct ib_uverbs_async_event_file *ev_file;
	struct file *filp;

	ev_file = kzalloc(sizeof(*ev_file), GFP_KERNEL);
	if (!ev_file)
		return ERR_PTR(-ENOMEM);

	ib_uverbs_init_event_queue(&ev_file->ev_queue);
	ev_file->uverbs_file = uverbs_file;
	kref_get(&ev_file->uverbs_file->ref);
	kref_init(&ev_file->ref);
	filp = anon_inode_getfile("[infinibandevent]", &uverbs_async_event_fops,
				  ev_file, O_RDONLY);
	if (IS_ERR(filp))
		goto err_put_refs;

	mutex_lock(&uverbs_file->device->lists_mutex);
	list_add_tail(&ev_file->list,
		      &uverbs_file->device->uverbs_events_file_list);
	mutex_unlock(&uverbs_file->device->lists_mutex);

	WARN_ON(uverbs_file->async_file);
	uverbs_file->async_file = ev_file;
	kref_get(&uverbs_file->async_file->ref);
	INIT_IB_EVENT_HANDLER(&uverbs_file->event_handler,
			      ib_dev,
			      ib_uverbs_event_handler);
	ib_register_event_handler(&uverbs_file->event_handler);
	/* At that point async file stuff was fully set */

	return filp;

err_put_refs:
	kref_put(&ev_file->uverbs_file->ref, ib_uverbs_release_file);
	kref_put(&ev_file->ref, ib_uverbs_release_async_event_file);
	return filp;
}