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
struct device_queue_manager {int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_interrupts (struct device_queue_manager*) ; 
 int pm_init (int /*<<< orphan*/ *,struct device_queue_manager*) ; 

__attribute__((used)) static int start_nocpsch(struct device_queue_manager *dqm)
{
	init_interrupts(dqm);
	return pm_init(&dqm->packets, dqm);
}