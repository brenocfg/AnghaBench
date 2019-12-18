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
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_seq {scalar_t__ state; scalar_t__ completion; int /*<<< orphan*/  (* callback ) (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*) ;int /*<<< orphan*/  id; } ;
struct nvkm_msgqueue_hdr {size_t seq_id; } ;
struct nvkm_msgqueue {struct nvkm_msgqueue_seq* seq; TYPE_1__* falcon; } ;
struct TYPE_2__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SEQ_STATE_CANCELLED ; 
 scalar_t__ SEQ_STATE_USED ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  msgqueue_seq_release (struct nvkm_msgqueue*,struct nvkm_msgqueue_seq*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*) ; 

__attribute__((used)) static int
msgqueue_msg_handle(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_hdr *hdr)
{
	const struct nvkm_subdev *subdev = priv->falcon->owner;
	struct nvkm_msgqueue_seq *seq;

	seq = &priv->seq[hdr->seq_id];
	if (seq->state != SEQ_STATE_USED && seq->state != SEQ_STATE_CANCELLED) {
		nvkm_error(subdev, "msg for unknown sequence %d", seq->id);
		return -EINVAL;
	}

	if (seq->state == SEQ_STATE_USED) {
		if (seq->callback)
			seq->callback(priv, hdr);
	}

	if (seq->completion)
		complete(seq->completion);

	msgqueue_seq_release(priv, seq);

	return 0;
}