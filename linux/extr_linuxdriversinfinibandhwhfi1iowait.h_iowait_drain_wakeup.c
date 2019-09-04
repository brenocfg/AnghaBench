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
struct iowait {int /*<<< orphan*/  (* sdma_drained ) (struct iowait*) ;int /*<<< orphan*/  wait_pio; int /*<<< orphan*/  wait_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iowait*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iowait_drain_wakeup(struct iowait *wait)
{
	wake_up(&wait->wait_dma);
	wake_up(&wait->wait_pio);
	if (wait->sdma_drained)
		wait->sdma_drained(wait);
}