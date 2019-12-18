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
struct virtio_input_event {int dummy; } ;
struct virtio_input {int /*<<< orphan*/  evt; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,struct virtio_input_event*,int) ; 
 int /*<<< orphan*/  virtqueue_add_inbuf (int /*<<< orphan*/ ,struct scatterlist*,int,struct virtio_input_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtinput_queue_evtbuf(struct virtio_input *vi,
				   struct virtio_input_event *evtbuf)
{
	struct scatterlist sg[1];

	sg_init_one(sg, evtbuf, sizeof(*evtbuf));
	virtqueue_add_inbuf(vi->evt, sg, 1, evtbuf, GFP_ATOMIC);
}