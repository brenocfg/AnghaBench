#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {int* status_ptr; unsigned int event_wrap; int event_counter; scalar_t__ (* wait_evnt ) (TYPE_3__*,int) ;TYPE_2__* dma_pages; int /*<<< orphan*/  fake_dma; int /*<<< orphan*/ * cmd_dma; } ;
typedef  TYPE_3__ drm_savage_private_t ;
struct TYPE_6__ {unsigned int wrap; int event; } ;
struct TYPE_7__ {TYPE_1__ age; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int SAVAGE_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVAGE_STATUS_WORD1 ; 
 int /*<<< orphan*/  UPDATE_EVENT_COUNTER () ; 
 scalar_t__ stub1 (TYPE_3__*,int) ; 

void savage_dma_wait(drm_savage_private_t * dev_priv, unsigned int page)
{
	uint16_t event;
	unsigned int wrap;

	/* Faked DMA buffer pages don't age. */
	if (dev_priv->cmd_dma == &dev_priv->fake_dma)
		return;

	UPDATE_EVENT_COUNTER();
	if (dev_priv->status_ptr)
		event = dev_priv->status_ptr[1] & 0xffff;
	else
		event = SAVAGE_READ(SAVAGE_STATUS_WORD1) & 0xffff;
	wrap = dev_priv->event_wrap;
	if (event > dev_priv->event_counter)
		wrap--;		/* hardware hasn't passed the last wrap yet */

	if (dev_priv->dma_pages[page].age.wrap > wrap ||
	    (dev_priv->dma_pages[page].age.wrap == wrap &&
	     dev_priv->dma_pages[page].age.event > event)) {
		if (dev_priv->wait_evnt(dev_priv,
					dev_priv->dma_pages[page].age.event)
		    < 0)
			DRM_ERROR("wait_evnt failed!\n");
	}
}