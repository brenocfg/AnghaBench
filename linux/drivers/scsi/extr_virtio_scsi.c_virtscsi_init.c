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
typedef  char const vq_callback_t ;
typedef  size_t u32 ;
typedef  char const virtqueue ;
struct virtio_scsi {size_t num_queues; int /*<<< orphan*/ * req_vqs; int /*<<< orphan*/  event_vq; int /*<<< orphan*/  ctrl_vq; } ;
struct virtio_device {int dummy; } ;
struct irq_affinity {int pre_vectors; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_SCSI_CDB_SIZE ; 
 int /*<<< orphan*/  VIRTIO_SCSI_SENSE_SIZE ; 
 size_t VIRTIO_SCSI_VQ_BASE ; 
 int /*<<< orphan*/  cdb_size ; 
 int /*<<< orphan*/  kfree (char const**) ; 
 char** kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sense_size ; 
 int virtio_find_vqs (struct virtio_device*,size_t,char const**,char const**,char const**,struct irq_affinity*) ; 
 int /*<<< orphan*/  virtscsi_config_set (struct virtio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* virtscsi_ctrl_done ; 
 char* virtscsi_event_done ; 
 int /*<<< orphan*/  virtscsi_init_vq (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  virtscsi_remove_vqs (struct virtio_device*) ; 
 char* virtscsi_req_done ; 

__attribute__((used)) static int virtscsi_init(struct virtio_device *vdev,
			 struct virtio_scsi *vscsi)
{
	int err;
	u32 i;
	u32 num_vqs;
	vq_callback_t **callbacks;
	const char **names;
	struct virtqueue **vqs;
	struct irq_affinity desc = { .pre_vectors = 2 };

	num_vqs = vscsi->num_queues + VIRTIO_SCSI_VQ_BASE;
	vqs = kmalloc_array(num_vqs, sizeof(struct virtqueue *), GFP_KERNEL);
	callbacks = kmalloc_array(num_vqs, sizeof(vq_callback_t *),
				  GFP_KERNEL);
	names = kmalloc_array(num_vqs, sizeof(char *), GFP_KERNEL);

	if (!callbacks || !vqs || !names) {
		err = -ENOMEM;
		goto out;
	}

	callbacks[0] = virtscsi_ctrl_done;
	callbacks[1] = virtscsi_event_done;
	names[0] = "control";
	names[1] = "event";
	for (i = VIRTIO_SCSI_VQ_BASE; i < num_vqs; i++) {
		callbacks[i] = virtscsi_req_done;
		names[i] = "request";
	}

	/* Discover virtqueues and write information to configuration.  */
	err = virtio_find_vqs(vdev, num_vqs, vqs, callbacks, names, &desc);
	if (err)
		goto out;

	virtscsi_init_vq(&vscsi->ctrl_vq, vqs[0]);
	virtscsi_init_vq(&vscsi->event_vq, vqs[1]);
	for (i = VIRTIO_SCSI_VQ_BASE; i < num_vqs; i++)
		virtscsi_init_vq(&vscsi->req_vqs[i - VIRTIO_SCSI_VQ_BASE],
				 vqs[i]);

	virtscsi_config_set(vdev, cdb_size, VIRTIO_SCSI_CDB_SIZE);
	virtscsi_config_set(vdev, sense_size, VIRTIO_SCSI_SENSE_SIZE);

	err = 0;

out:
	kfree(names);
	kfree(callbacks);
	kfree(vqs);
	if (err)
		virtscsi_remove_vqs(vdev);
	return err;
}