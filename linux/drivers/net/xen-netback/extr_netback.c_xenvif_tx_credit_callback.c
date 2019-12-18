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
struct xenvif_queue {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  credit_timeout ; 
 struct xenvif_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct xenvif_queue* queue ; 
 int /*<<< orphan*/  tx_add_credit (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_napi_schedule_or_enable_events (struct xenvif_queue*) ; 

void xenvif_tx_credit_callback(struct timer_list *t)
{
	struct xenvif_queue *queue = from_timer(queue, t, credit_timeout);
	tx_add_credit(queue);
	xenvif_napi_schedule_or_enable_events(queue);
}