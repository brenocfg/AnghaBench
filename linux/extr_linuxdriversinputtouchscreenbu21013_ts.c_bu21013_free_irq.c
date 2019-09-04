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
struct bu21013_ts_data {int touch_stopped; int /*<<< orphan*/  irq; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bu21013_free_irq(struct bu21013_ts_data *bu21013_data)
{
	bu21013_data->touch_stopped = true;
	wake_up(&bu21013_data->wait);
	free_irq(bu21013_data->irq, bu21013_data);
}