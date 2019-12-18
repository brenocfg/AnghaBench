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
typedef  int /*<<< orphan*/  vq_callback_t ;
struct virtqueue {int dummy; } ;
struct virtio_input {struct virtqueue* sts; struct virtqueue* evt; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * virtinput_recv_events ; 
 int /*<<< orphan*/ * virtinput_recv_status ; 
 int virtio_find_vqs (int /*<<< orphan*/ ,int,struct virtqueue**,int /*<<< orphan*/ **,char const* const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtinput_init_vqs(struct virtio_input *vi)
{
	struct virtqueue *vqs[2];
	vq_callback_t *cbs[] = { virtinput_recv_events,
				 virtinput_recv_status };
	static const char * const names[] = { "events", "status" };
	int err;

	err = virtio_find_vqs(vi->vdev, 2, vqs, cbs, names, NULL);
	if (err)
		return err;
	vi->evt = vqs[0];
	vi->sts = vqs[1];

	return 0;
}