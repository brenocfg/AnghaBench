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
struct packet_manager {int /*<<< orphan*/  priv_queue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_queue_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void pm_uninit(struct packet_manager *pm)
{
	mutex_destroy(&pm->lock);
	kernel_queue_uninit(pm->priv_queue);
}