#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct xvip_dma {TYPE_1__ pipe; int /*<<< orphan*/  lock; TYPE_2__ video; scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (TYPE_2__*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_2__*) ; 

void xvip_dma_cleanup(struct xvip_dma *dma)
{
	if (video_is_registered(&dma->video))
		video_unregister_device(&dma->video);

	if (dma->dma)
		dma_release_channel(dma->dma);

	media_entity_cleanup(&dma->video.entity);

	mutex_destroy(&dma->lock);
	mutex_destroy(&dma->pipe.lock);
}