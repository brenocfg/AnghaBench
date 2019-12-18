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
struct TYPE_2__ {int run; int /*<<< orphan*/  work; int /*<<< orphan*/  workq; int /*<<< orphan*/  lock; } ;
struct gm12u320_device {TYPE_1__ fb_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gm12u320_start_fb_update(struct gm12u320_device *gm12u320)
{
	mutex_lock(&gm12u320->fb_update.lock);
	gm12u320->fb_update.run = true;
	mutex_unlock(&gm12u320->fb_update.lock);

	queue_work(gm12u320->fb_update.workq, &gm12u320->fb_update.work);
}