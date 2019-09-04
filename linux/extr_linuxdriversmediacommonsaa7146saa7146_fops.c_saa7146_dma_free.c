#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {int /*<<< orphan*/  dev; } ;
struct videobuf_dmabuf {int dummy; } ;
struct saa7146_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct saa7146_buf {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_dev*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  videobuf_dma_free (struct videobuf_dmabuf*) ; 
 int /*<<< orphan*/  videobuf_dma_unmap (int /*<<< orphan*/ ,struct videobuf_dmabuf*) ; 
 struct videobuf_dmabuf* videobuf_to_dma (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_waiton (struct videobuf_queue*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void saa7146_dma_free(struct saa7146_dev *dev,struct videobuf_queue *q,
						struct saa7146_buf *buf)
{
	struct videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);
	DEB_EE("dev:%p, buf:%p\n", dev, buf);

	BUG_ON(in_interrupt());

	videobuf_waiton(q, &buf->vb, 0, 0);
	videobuf_dma_unmap(q->dev, dma);
	videobuf_dma_free(dma);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}