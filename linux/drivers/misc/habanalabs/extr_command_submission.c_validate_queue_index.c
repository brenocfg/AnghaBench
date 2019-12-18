#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct hw_queue_properties {scalar_t__ type; scalar_t__ driver_only; } ;
struct asic_fixed_properties {struct hw_queue_properties* hw_queues_props; } ;
struct hl_device {int /*<<< orphan*/  dev; struct asic_fixed_properties asic_prop; } ;
struct hl_cs_chunk {size_t queue_index; int cb_handle; int cb_size; } ;
struct hl_cb_mgr {int dummy; } ;
struct hl_cb {scalar_t__ size; int /*<<< orphan*/  lock; int /*<<< orphan*/  cs_cnt; } ;

/* Variables and functions */
 size_t HL_MAX_QUEUES ; 
 int PAGE_SHIFT ; 
 scalar_t__ QUEUE_TYPE_INT ; 
 scalar_t__ QUEUE_TYPE_NA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct hl_cb* hl_cb_get (struct hl_device*,struct hl_cb_mgr*,scalar_t__) ; 
 int /*<<< orphan*/  hl_cb_put (struct hl_cb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hl_cb *validate_queue_index(struct hl_device *hdev,
					struct hl_cb_mgr *cb_mgr,
					struct hl_cs_chunk *chunk,
					bool *ext_queue)
{
	struct asic_fixed_properties *asic = &hdev->asic_prop;
	struct hw_queue_properties *hw_queue_prop;
	u32 cb_handle;
	struct hl_cb *cb;

	/* Assume external queue */
	*ext_queue = true;

	hw_queue_prop = &asic->hw_queues_props[chunk->queue_index];

	if ((chunk->queue_index >= HL_MAX_QUEUES) ||
			(hw_queue_prop->type == QUEUE_TYPE_NA)) {
		dev_err(hdev->dev, "Queue index %d is invalid\n",
			chunk->queue_index);
		return NULL;
	}

	if (hw_queue_prop->driver_only) {
		dev_err(hdev->dev,
			"Queue index %d is restricted for the kernel driver\n",
			chunk->queue_index);
		return NULL;
	} else if (hw_queue_prop->type == QUEUE_TYPE_INT) {
		*ext_queue = false;
		return (struct hl_cb *) (uintptr_t) chunk->cb_handle;
	}

	/* Retrieve CB object */
	cb_handle = (u32) (chunk->cb_handle >> PAGE_SHIFT);

	cb = hl_cb_get(hdev, cb_mgr, cb_handle);
	if (!cb) {
		dev_err(hdev->dev, "CB handle 0x%x invalid\n", cb_handle);
		return NULL;
	}

	if ((chunk->cb_size < 8) || (chunk->cb_size > cb->size)) {
		dev_err(hdev->dev, "CB size %u invalid\n", chunk->cb_size);
		goto release_cb;
	}

	spin_lock(&cb->lock);
	cb->cs_cnt++;
	spin_unlock(&cb->lock);

	return cb;

release_cb:
	hl_cb_put(cb);
	return NULL;
}