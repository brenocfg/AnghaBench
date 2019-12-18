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
struct queue_properties {int /*<<< orphan*/  doorbell_off; } ;
struct kfd_process_device {int dummy; } ;
struct kfd_process {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pqm; int /*<<< orphan*/  pasid; } ;
struct kfd_ioctl_create_queue_args {unsigned int gpu_id; unsigned int queue_id; unsigned int ring_base_address; unsigned int read_pointer_address; unsigned int write_pointer_address; int /*<<< orphan*/  doorbell_offset; } ;
struct kfd_dev {TYPE_1__* device_info; int /*<<< orphan*/  id; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  asic_family; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ IS_ERR (struct kfd_process_device*) ; 
 scalar_t__ KFD_IS_SOC15 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KFD_MMAP_GPU_ID (unsigned int) ; 
 int /*<<< orphan*/  KFD_MMAP_TYPE_DOORBELL ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 struct kfd_process_device* kfd_bind_process_to_device (struct kfd_dev*,struct kfd_process*) ; 
 struct kfd_dev* kfd_device_by_id (unsigned int) ; 
 int /*<<< orphan*/  memset (struct queue_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pqm_create_queue (int /*<<< orphan*/ *,struct kfd_dev*,struct file*,struct queue_properties*,unsigned int*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int set_queue_properties_from_user (struct queue_properties*,struct kfd_ioctl_create_queue_args*) ; 

__attribute__((used)) static int kfd_ioctl_create_queue(struct file *filep, struct kfd_process *p,
					void *data)
{
	struct kfd_ioctl_create_queue_args *args = data;
	struct kfd_dev *dev;
	int err = 0;
	unsigned int queue_id;
	struct kfd_process_device *pdd;
	struct queue_properties q_properties;

	memset(&q_properties, 0, sizeof(struct queue_properties));

	pr_debug("Creating queue ioctl\n");

	err = set_queue_properties_from_user(&q_properties, args);
	if (err)
		return err;

	pr_debug("Looking for gpu id 0x%x\n", args->gpu_id);
	dev = kfd_device_by_id(args->gpu_id);
	if (!dev) {
		pr_debug("Could not find gpu id 0x%x\n", args->gpu_id);
		return -EINVAL;
	}

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	if (IS_ERR(pdd)) {
		err = -ESRCH;
		goto err_bind_process;
	}

	pr_debug("Creating queue for PASID %d on gpu 0x%x\n",
			p->pasid,
			dev->id);

	err = pqm_create_queue(&p->pqm, dev, filep, &q_properties, &queue_id);
	if (err != 0)
		goto err_create_queue;

	args->queue_id = queue_id;


	/* Return gpu_id as doorbell offset for mmap usage */
	args->doorbell_offset = KFD_MMAP_TYPE_DOORBELL;
	args->doorbell_offset |= KFD_MMAP_GPU_ID(args->gpu_id);
	args->doorbell_offset <<= PAGE_SHIFT;
	if (KFD_IS_SOC15(dev->device_info->asic_family))
		/* On SOC15 ASICs, doorbell allocation must be
		 * per-device, and independent from the per-process
		 * queue_id. Return the doorbell offset within the
		 * doorbell aperture to user mode.
		 */
		args->doorbell_offset |= q_properties.doorbell_off;

	mutex_unlock(&p->mutex);

	pr_debug("Queue id %d was created successfully\n", args->queue_id);

	pr_debug("Ring buffer address == 0x%016llX\n",
			args->ring_base_address);

	pr_debug("Read ptr address    == 0x%016llX\n",
			args->read_pointer_address);

	pr_debug("Write ptr address   == 0x%016llX\n",
			args->write_pointer_address);

	return 0;

err_create_queue:
err_bind_process:
	mutex_unlock(&p->mutex);
	return err;
}