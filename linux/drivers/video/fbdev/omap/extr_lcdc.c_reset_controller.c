#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  disable_controller_async () ; 
 int /*<<< orphan*/  enable_controller () ; 
 unsigned long jiffies ; 
 TYPE_2__ lcdc ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static void reset_controller(u32 status)
{
	static unsigned long reset_count;
	static unsigned long last_jiffies;

	disable_controller_async();
	reset_count++;
	if (reset_count == 1 || time_after(jiffies, last_jiffies + HZ)) {
		dev_err(lcdc.fbdev->dev,
			  "resetting (status %#010x,reset count %lu)\n",
			  status, reset_count);
		last_jiffies = jiffies;
	}
	if (reset_count < 100) {
		enable_controller();
	} else {
		reset_count = 0;
		dev_err(lcdc.fbdev->dev,
			"too many reset attempts, giving up.\n");
	}
}