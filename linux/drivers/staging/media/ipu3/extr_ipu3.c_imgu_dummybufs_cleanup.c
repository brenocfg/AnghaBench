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
struct TYPE_2__ {int /*<<< orphan*/  dmap; } ;

/* Variables and functions */
 unsigned int IPU3_CSS_QUEUES ; 
 int /*<<< orphan*/  imgu_dmamap_free (struct imgu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imgu_dummybufs_cleanup(struct imgu_device *imgu, unsigned int pipe)
{
	unsigned int i;
	struct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	for (i = 0; i < IPU3_CSS_QUEUES; i++)
		imgu_dmamap_free(imgu,
				 &imgu_pipe->queues[i].dmap);
}