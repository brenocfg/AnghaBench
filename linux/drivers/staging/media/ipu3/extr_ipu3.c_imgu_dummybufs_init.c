#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {TYPE_4__* plane_fmt; } ;
struct v4l2_meta_format {size_t buffersize; } ;
struct imgu_media_pipe {TYPE_5__* queues; TYPE_3__* nodes; int /*<<< orphan*/ * queue_enabled; } ;
struct imgu_device {struct imgu_media_pipe* imgu_pipe; } ;
struct TYPE_12__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_11__ {TYPE_6__ dmap; int /*<<< orphan*/ * dummybufs; } ;
struct TYPE_10__ {size_t sizeimage; } ;
struct TYPE_7__ {struct v4l2_pix_format_mplane pix_mp; struct v4l2_meta_format meta; } ;
struct TYPE_8__ {TYPE_1__ fmt; } ;
struct TYPE_9__ {TYPE_2__ vdev_fmt; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int IMGU_MAX_QUEUE_DEPTH ; 
 unsigned int IMGU_NODE_PARAMS ; 
 unsigned int IMGU_NODE_STAT_3A ; 
 size_t IMGU_NODE_VF ; 
 unsigned int IMGU_QUEUE_MASTER ; 
 unsigned int IPU3_CSS_QUEUES ; 
 unsigned int IPU3_CSS_QUEUE_VF ; 
 int /*<<< orphan*/  imgu_css_buf_init (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ imgu_css_dma_buffer_resize (struct imgu_device*,TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  imgu_dummybufs_cleanup (struct imgu_device*,unsigned int) ; 
 unsigned int imgu_map_node (struct imgu_device*,unsigned int) ; 

__attribute__((used)) static int imgu_dummybufs_init(struct imgu_device *imgu, unsigned int pipe)
{
	const struct v4l2_pix_format_mplane *mpix;
	const struct v4l2_meta_format	*meta;
	unsigned int i, k, node;
	size_t size;
	struct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* Allocate a dummy buffer for each queue where buffer is optional */
	for (i = 0; i < IPU3_CSS_QUEUES; i++) {
		node = imgu_map_node(imgu, i);
		if (!imgu_pipe->queue_enabled[node] || i == IMGU_QUEUE_MASTER)
			continue;

		if (!imgu_pipe->nodes[IMGU_NODE_VF].enabled &&
		    i == IPU3_CSS_QUEUE_VF)
			/*
			 * Do not enable dummy buffers for VF if it is not
			 * requested by the user.
			 */
			continue;

		meta = &imgu_pipe->nodes[node].vdev_fmt.fmt.meta;
		mpix = &imgu_pipe->nodes[node].vdev_fmt.fmt.pix_mp;

		if (node == IMGU_NODE_STAT_3A || node == IMGU_NODE_PARAMS)
			size = meta->buffersize;
		else
			size = mpix->plane_fmt[0].sizeimage;

		if (imgu_css_dma_buffer_resize(imgu,
					       &imgu_pipe->queues[i].dmap,
					       size)) {
			imgu_dummybufs_cleanup(imgu, pipe);
			return -ENOMEM;
		}

		for (k = 0; k < IMGU_MAX_QUEUE_DEPTH; k++)
			imgu_css_buf_init(&imgu_pipe->queues[i].dummybufs[k], i,
					  imgu_pipe->queues[i].dmap.daddr);
	}

	return 0;
}