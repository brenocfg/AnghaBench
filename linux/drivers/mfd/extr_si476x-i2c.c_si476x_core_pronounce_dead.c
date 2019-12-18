#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct si476x_core {int /*<<< orphan*/  tuning; int /*<<< orphan*/  stc; int /*<<< orphan*/  command; int /*<<< orphan*/  cts; int /*<<< orphan*/  rds_read_queue; int /*<<< orphan*/  is_alive; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void si476x_core_pronounce_dead(struct si476x_core *core)
{
	dev_info(&core->client->dev, "Core device is dead.\n");

	atomic_set(&core->is_alive, 0);

	/* Wake up al possible waiting processes */
	wake_up_interruptible(&core->rds_read_queue);

	atomic_set(&core->cts, 1);
	wake_up(&core->command);

	atomic_set(&core->stc, 1);
	wake_up(&core->tuning);
}