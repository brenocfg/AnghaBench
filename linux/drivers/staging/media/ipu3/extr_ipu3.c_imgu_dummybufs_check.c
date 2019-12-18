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
struct imgu_media_pipe {TYPE_1__* queues; } ;
struct imgu_device {struct imgu_media_pipe* imgu_pipe; } ;
struct imgu_css_buffer {size_t queue; } ;
struct TYPE_2__ {struct imgu_css_buffer* dummybufs; } ;

/* Variables and functions */
 unsigned int IMGU_MAX_QUEUE_DEPTH ; 

__attribute__((used)) static bool imgu_dummybufs_check(struct imgu_device *imgu,
				 struct imgu_css_buffer *buf,
				 unsigned int pipe)
{
	unsigned int i;
	struct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	for (i = 0; i < IMGU_MAX_QUEUE_DEPTH; i++)
		if (buf == &imgu_pipe->queues[buf->queue].dummybufs[i])
			break;

	return i < IMGU_MAX_QUEUE_DEPTH;
}