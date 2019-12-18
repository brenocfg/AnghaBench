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
typedef  int /*<<< orphan*/  u16 ;
struct virtio_input_event {int /*<<< orphan*/  value; void* code; void* type; } ;
struct virtio_input {int /*<<< orphan*/  lock; int /*<<< orphan*/  sts; scalar_t__ ready; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtio_input_event*) ; 
 struct virtio_input_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,struct virtio_input_event*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virtqueue_add_outbuf (int /*<<< orphan*/ ,struct scatterlist*,int,struct virtio_input_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtinput_send_status(struct virtio_input *vi,
				 u16 type, u16 code, s32 value)
{
	struct virtio_input_event *stsbuf;
	struct scatterlist sg[1];
	unsigned long flags;
	int rc;

	stsbuf = kzalloc(sizeof(*stsbuf), GFP_ATOMIC);
	if (!stsbuf)
		return -ENOMEM;

	stsbuf->type  = cpu_to_le16(type);
	stsbuf->code  = cpu_to_le16(code);
	stsbuf->value = cpu_to_le32(value);
	sg_init_one(sg, stsbuf, sizeof(*stsbuf));

	spin_lock_irqsave(&vi->lock, flags);
	if (vi->ready) {
		rc = virtqueue_add_outbuf(vi->sts, sg, 1, stsbuf, GFP_ATOMIC);
		virtqueue_kick(vi->sts);
	} else {
		rc = -ENODEV;
	}
	spin_unlock_irqrestore(&vi->lock, flags);

	if (rc != 0)
		kfree(stsbuf);
	return rc;
}