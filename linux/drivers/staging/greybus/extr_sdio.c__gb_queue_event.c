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
typedef  int u8 ;
struct gb_sdio_host {int queued_events; } ;

/* Variables and functions */
 int GB_SDIO_CARD_INSERTED ; 
 int GB_SDIO_CARD_REMOVED ; 

__attribute__((used)) static void _gb_queue_event(struct gb_sdio_host *host, u8 event)
{
	if (event & GB_SDIO_CARD_INSERTED)
		host->queued_events &= ~GB_SDIO_CARD_REMOVED;
	else if (event & GB_SDIO_CARD_REMOVED)
		host->queued_events &= ~GB_SDIO_CARD_INSERTED;

	host->queued_events |= event;
}