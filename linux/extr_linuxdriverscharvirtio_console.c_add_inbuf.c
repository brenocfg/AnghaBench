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
struct virtqueue {int num_free; } ;
struct scatterlist {int dummy; } ;
struct port_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtqueue_add_inbuf (struct virtqueue*,struct scatterlist*,int,struct port_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static int add_inbuf(struct virtqueue *vq, struct port_buffer *buf)
{
	struct scatterlist sg[1];
	int ret;

	sg_init_one(sg, buf->buf, buf->size);

	ret = virtqueue_add_inbuf(vq, sg, 1, buf, GFP_ATOMIC);
	virtqueue_kick(vq);
	if (!ret)
		ret = vq->num_free;
	return ret;
}