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
struct skd_device {TYPE_1__* pdev; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ jiffies ; 
 int mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skd_timer_tick ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skd_start_timer(struct skd_device *skdev)
{
	int rc;

	timer_setup(&skdev->timer, skd_timer_tick, 0);

	rc = mod_timer(&skdev->timer, (jiffies + HZ));
	if (rc)
		dev_err(&skdev->pdev->dev, "failed to start timer %d\n", rc);
	return rc;
}