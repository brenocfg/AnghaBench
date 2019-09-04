#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; int vm_start; unsigned long vm_end; } ;
struct file {struct client* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pages; } ;
struct client {int vm_start; int buffer_is_mapped; TYPE_5__* device; TYPE_1__ buffer; int /*<<< orphan*/  lock; scalar_t__ iso_context; } ;
struct TYPE_7__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int VM_SHARED ; 
 scalar_t__ fw_device_is_shutdown (TYPE_5__*) ; 
 int fw_iso_buffer_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int fw_iso_buffer_map_dma (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fw_iso_buffer_map_vma (TYPE_1__*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  iso_dma_direction (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fw_device_op_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct client *client = file->private_data;
	unsigned long size;
	int page_count, ret;

	if (fw_device_is_shutdown(client->device))
		return -ENODEV;

	/* FIXME: We could support multiple buffers, but we don't. */
	if (client->buffer.pages != NULL)
		return -EBUSY;

	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	if (vma->vm_start & ~PAGE_MASK)
		return -EINVAL;

	client->vm_start = vma->vm_start;
	size = vma->vm_end - vma->vm_start;
	page_count = size >> PAGE_SHIFT;
	if (size & ~PAGE_MASK)
		return -EINVAL;

	ret = fw_iso_buffer_alloc(&client->buffer, page_count);
	if (ret < 0)
		return ret;

	spin_lock_irq(&client->lock);
	if (client->iso_context) {
		ret = fw_iso_buffer_map_dma(&client->buffer,
				client->device->card,
				iso_dma_direction(client->iso_context));
		client->buffer_is_mapped = (ret == 0);
	}
	spin_unlock_irq(&client->lock);
	if (ret < 0)
		goto fail;

	ret = fw_iso_buffer_map_vma(&client->buffer, vma);
	if (ret < 0)
		goto fail;

	return 0;
 fail:
	fw_iso_buffer_destroy(&client->buffer, client->device->card);
	return ret;
}