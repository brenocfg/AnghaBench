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
struct xenvif_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_REQUESTS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

void xenvif_napi_schedule_or_enable_events(struct xenvif_queue *queue)
{
	int more_to_do;

	RING_FINAL_CHECK_FOR_REQUESTS(&queue->tx, more_to_do);

	if (more_to_do)
		napi_schedule(&queue->napi);
}