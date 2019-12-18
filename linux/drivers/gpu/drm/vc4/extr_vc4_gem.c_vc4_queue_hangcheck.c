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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct vc4_dev {TYPE_1__ hangcheck; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void
vc4_queue_hangcheck(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	mod_timer(&vc4->hangcheck.timer,
		  round_jiffies_up(jiffies + msecs_to_jiffies(100)));
}