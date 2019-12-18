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
struct TYPE_2__ {scalar_t__ next; } ;
struct smscore_device_t {int num_buffers; int /*<<< orphan*/  entry; struct smscore_device_t* fw_buf; int /*<<< orphan*/  common_buffer_phys; struct smscore_device_t* common_buffer; int /*<<< orphan*/  common_buffer_size; int /*<<< orphan*/  device; scalar_t__ usb_device; TYPE_1__ buffers; } ;
struct smscore_buffer_t {int num_buffers; int /*<<< orphan*/  entry; struct smscore_buffer_t* fw_buf; int /*<<< orphan*/  common_buffer_phys; struct smscore_buffer_t* common_buffer; int /*<<< orphan*/  common_buffer_size; int /*<<< orphan*/  device; scalar_t__ usb_device; TYPE_1__ buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smscore_device_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_smscore_deviceslock ; 
 int /*<<< orphan*/  kfree (struct smscore_device_t*) ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  sms_ir_exit (struct smscore_device_t*) ; 
 int /*<<< orphan*/  smscore_notify_callbacks (struct smscore_device_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_notify_clients (struct smscore_device_t*) ; 

void smscore_unregister_device(struct smscore_device_t *coredev)
{
	struct smscore_buffer_t *cb;
	int num_buffers = 0;
	int retry = 0;

	kmutex_lock(&g_smscore_deviceslock);

	/* Release input device (IR) resources */
	sms_ir_exit(coredev);

	smscore_notify_clients(coredev);
	smscore_notify_callbacks(coredev, NULL, 0);

	/* at this point all buffers should be back
	 * onresponse must no longer be called */

	while (1) {
		while (!list_empty(&coredev->buffers)) {
			cb = (struct smscore_buffer_t *) coredev->buffers.next;
			list_del(&cb->entry);
			kfree(cb);
			num_buffers++;
		}
		if (num_buffers == coredev->num_buffers)
			break;
		if (++retry > 10) {
			pr_info("exiting although not all buffers released.\n");
			break;
		}

		pr_debug("waiting for %d buffer(s)\n",
			 coredev->num_buffers - num_buffers);
		kmutex_unlock(&g_smscore_deviceslock);
		msleep(100);
		kmutex_lock(&g_smscore_deviceslock);
	}

	pr_debug("freed %d buffers\n", num_buffers);

	if (coredev->common_buffer) {
		if (coredev->usb_device)
			kfree(coredev->common_buffer);
		else
			dma_free_coherent(coredev->device,
					  coredev->common_buffer_size,
					  coredev->common_buffer,
					  coredev->common_buffer_phys);
	}
	kfree(coredev->fw_buf);

	list_del(&coredev->entry);
	kfree(coredev);

	kmutex_unlock(&g_smscore_deviceslock);

	pr_debug("device %p destroyed\n", coredev);
}