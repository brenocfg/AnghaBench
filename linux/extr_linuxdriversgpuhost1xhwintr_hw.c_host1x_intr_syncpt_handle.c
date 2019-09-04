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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct host1x_syncpt {unsigned int id; TYPE_1__ intr; struct host1x* host; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS (unsigned int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE (unsigned int) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void host1x_intr_syncpt_handle(struct host1x_syncpt *syncpt)
{
	unsigned int id = syncpt->id;
	struct host1x *host = syncpt->host;

	host1x_sync_writel(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE(id / 32));
	host1x_sync_writel(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(id / 32));

	schedule_work(&syncpt->intr.work);
}