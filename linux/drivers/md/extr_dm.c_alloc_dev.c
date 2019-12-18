#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  completion; } ;
struct mapped_device {int numa_node_id; int init_tio_pdu; int /*<<< orphan*/  stats; int /*<<< orphan*/  bdev; TYPE_4__* disk; int /*<<< orphan*/  wq; int /*<<< orphan*/  name; int /*<<< orphan*/  dax_dev; TYPE_3__* queue; TYPE_2__ kobj_holder; int /*<<< orphan*/  eventq; int /*<<< orphan*/  work; int /*<<< orphan*/  wait; int /*<<< orphan*/  uevent_lock; int /*<<< orphan*/  table_devices; int /*<<< orphan*/  uevent_list; int /*<<< orphan*/  uevent_seq; int /*<<< orphan*/  event_nr; int /*<<< orphan*/  open_count; int /*<<< orphan*/  holders; int /*<<< orphan*/  deferred_lock; int /*<<< orphan*/  table_devices_lock; int /*<<< orphan*/  type_lock; int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  type; int /*<<< orphan*/  io_barrier; } ;
struct TYPE_10__ {int first_minor; int /*<<< orphan*/  disk_name; struct mapped_device* private_data; TYPE_3__* queue; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
struct TYPE_9__ {TYPE_1__* backing_dev_info; struct mapped_device* queuedata; } ;
struct TYPE_7__ {struct mapped_device* congested_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_DAX_DRIVER ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int DM_ANY_MINOR ; 
 int /*<<< orphan*/  DM_TYPE_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 void* MINOR_ALLOCED ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  _major ; 
 int /*<<< orphan*/  _minor_idr ; 
 int /*<<< orphan*/  _minor_lock ; 
 int /*<<< orphan*/  add_disk_no_queue_reg (TYPE_4__*) ; 
 int /*<<< orphan*/  alloc_dax (struct mapped_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* alloc_disk_node (int,int) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bdget_disk (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* blk_alloc_queue_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cleanup_mapped_device (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_blk_dops ; 
 int /*<<< orphan*/  dm_dax_ops ; 
 int dm_get_numa_node () ; 
 int /*<<< orphan*/  dm_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_wq_work ; 
 int /*<<< orphan*/  format_dev_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_minor (int) ; 
 void* idr_replace (int /*<<< orphan*/ *,struct mapped_device*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (struct mapped_device*) ; 
 struct mapped_device* kvzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int next_free_minor (int*) ; 
 int specific_minor (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mapped_device *alloc_dev(int minor)
{
	int r, numa_node_id = dm_get_numa_node();
	struct mapped_device *md;
	void *old_md;

	md = kvzalloc_node(sizeof(*md), GFP_KERNEL, numa_node_id);
	if (!md) {
		DMWARN("unable to allocate device, out of memory.");
		return NULL;
	}

	if (!try_module_get(THIS_MODULE))
		goto bad_module_get;

	/* get a minor number for the dev */
	if (minor == DM_ANY_MINOR)
		r = next_free_minor(&minor);
	else
		r = specific_minor(minor);
	if (r < 0)
		goto bad_minor;

	r = init_srcu_struct(&md->io_barrier);
	if (r < 0)
		goto bad_io_barrier;

	md->numa_node_id = numa_node_id;
	md->init_tio_pdu = false;
	md->type = DM_TYPE_NONE;
	mutex_init(&md->suspend_lock);
	mutex_init(&md->type_lock);
	mutex_init(&md->table_devices_lock);
	spin_lock_init(&md->deferred_lock);
	atomic_set(&md->holders, 1);
	atomic_set(&md->open_count, 0);
	atomic_set(&md->event_nr, 0);
	atomic_set(&md->uevent_seq, 0);
	INIT_LIST_HEAD(&md->uevent_list);
	INIT_LIST_HEAD(&md->table_devices);
	spin_lock_init(&md->uevent_lock);

	md->queue = blk_alloc_queue_node(GFP_KERNEL, numa_node_id);
	if (!md->queue)
		goto bad;
	md->queue->queuedata = md;
	md->queue->backing_dev_info->congested_data = md;

	md->disk = alloc_disk_node(1, md->numa_node_id);
	if (!md->disk)
		goto bad;

	init_waitqueue_head(&md->wait);
	INIT_WORK(&md->work, dm_wq_work);
	init_waitqueue_head(&md->eventq);
	init_completion(&md->kobj_holder.completion);

	md->disk->major = _major;
	md->disk->first_minor = minor;
	md->disk->fops = &dm_blk_dops;
	md->disk->queue = md->queue;
	md->disk->private_data = md;
	sprintf(md->disk->disk_name, "dm-%d", minor);

	if (IS_ENABLED(CONFIG_DAX_DRIVER)) {
		md->dax_dev = alloc_dax(md, md->disk->disk_name,
					&dm_dax_ops, 0);
		if (!md->dax_dev)
			goto bad;
	}

	add_disk_no_queue_reg(md->disk);
	format_dev_t(md->name, MKDEV(_major, minor));

	md->wq = alloc_workqueue("kdmflush", WQ_MEM_RECLAIM, 0);
	if (!md->wq)
		goto bad;

	md->bdev = bdget_disk(md->disk, 0);
	if (!md->bdev)
		goto bad;

	dm_stats_init(&md->stats);

	/* Populate the mapping, nobody knows we exist yet */
	spin_lock(&_minor_lock);
	old_md = idr_replace(&_minor_idr, md, minor);
	spin_unlock(&_minor_lock);

	BUG_ON(old_md != MINOR_ALLOCED);

	return md;

bad:
	cleanup_mapped_device(md);
bad_io_barrier:
	free_minor(minor);
bad_minor:
	module_put(THIS_MODULE);
bad_module_get:
	kvfree(md);
	return NULL;
}