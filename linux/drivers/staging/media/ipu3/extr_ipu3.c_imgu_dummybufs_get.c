#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imgu_media_pipe {TYPE_2__* queues; } ;
struct imgu_device {struct imgu_media_pipe* imgu_pipe; } ;
struct imgu_css_buffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  vaddr; } ;
struct TYPE_4__ {struct imgu_css_buffer* dummybufs; TYPE_1__ dmap; } ;

/* Variables and functions */
 unsigned int IMGU_MAX_QUEUE_DEPTH ; 
 scalar_t__ IPU3_CSS_BUFFER_QUEUED ; 
 int IPU3_CSS_QUEUE_IN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  imgu_css_buf_init (struct imgu_css_buffer*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ imgu_css_buf_state (struct imgu_css_buffer*) ; 

__attribute__((used)) static struct imgu_css_buffer *imgu_dummybufs_get(struct imgu_device *imgu,
						   int queue, unsigned int pipe)
{
	unsigned int i;
	struct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* dummybufs are not allocated for master q */
	if (queue == IPU3_CSS_QUEUE_IN)
		return NULL;

	if (WARN_ON(!imgu_pipe->queues[queue].dmap.vaddr))
		/* Buffer should not be allocated here */
		return NULL;

	for (i = 0; i < IMGU_MAX_QUEUE_DEPTH; i++)
		if (imgu_css_buf_state(&imgu_pipe->queues[queue].dummybufs[i]) !=
			IPU3_CSS_BUFFER_QUEUED)
			break;

	if (i == IMGU_MAX_QUEUE_DEPTH)
		return NULL;

	imgu_css_buf_init(&imgu_pipe->queues[queue].dummybufs[i], queue,
			  imgu_pipe->queues[queue].dmap.daddr);

	return &imgu_pipe->queues[queue].dummybufs[i];
}