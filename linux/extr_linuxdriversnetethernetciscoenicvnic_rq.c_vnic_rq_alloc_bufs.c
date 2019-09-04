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
typedef  int /*<<< orphan*/  u8 ;
struct vnic_rq_buf {unsigned int index; struct vnic_rq_buf* next; int /*<<< orphan*/ * desc; } ;
struct TYPE_2__ {unsigned int desc_count; int desc_size; scalar_t__ descs; } ;
struct vnic_rq {struct vnic_rq_buf** bufs; struct vnic_rq_buf* to_clean; struct vnic_rq_buf* to_use; TYPE_1__ ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int VNIC_RQ_BUF_BLKS_NEEDED (unsigned int) ; 
 unsigned int VNIC_RQ_BUF_BLK_ENTRIES (unsigned int) ; 
 int /*<<< orphan*/  VNIC_RQ_BUF_BLK_SZ (unsigned int) ; 
 struct vnic_rq_buf* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnic_rq_alloc_bufs(struct vnic_rq *rq)
{
	struct vnic_rq_buf *buf;
	unsigned int i, j, count = rq->ring.desc_count;
	unsigned int blks = VNIC_RQ_BUF_BLKS_NEEDED(count);

	for (i = 0; i < blks; i++) {
		rq->bufs[i] = kzalloc(VNIC_RQ_BUF_BLK_SZ(count), GFP_KERNEL);
		if (!rq->bufs[i])
			return -ENOMEM;
	}

	for (i = 0; i < blks; i++) {
		buf = rq->bufs[i];
		for (j = 0; j < VNIC_RQ_BUF_BLK_ENTRIES(count); j++) {
			buf->index = i * VNIC_RQ_BUF_BLK_ENTRIES(count) + j;
			buf->desc = (u8 *)rq->ring.descs +
				rq->ring.desc_size * buf->index;
			if (buf->index + 1 == count) {
				buf->next = rq->bufs[0];
				break;
			} else if (j + 1 == VNIC_RQ_BUF_BLK_ENTRIES(count)) {
				buf->next = rq->bufs[i + 1];
			} else {
				buf->next = buf + 1;
				buf++;
			}
		}
	}

	rq->to_use = rq->to_clean = rq->bufs[0];

	return 0;
}