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
struct timer_list {int dummy; } ;
struct sxgbe_tx_queue {int dummy; } ;

/* Variables and functions */
 struct sxgbe_tx_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sxgbe_tx_queue* p ; 
 int /*<<< orphan*/  sxgbe_tx_queue_clean (struct sxgbe_tx_queue*) ; 
 int /*<<< orphan*/  txtimer ; 

__attribute__((used)) static void sxgbe_tx_timer(struct timer_list *t)
{
	struct sxgbe_tx_queue *p = from_timer(p, t, txtimer);
	sxgbe_tx_queue_clean(p);
}