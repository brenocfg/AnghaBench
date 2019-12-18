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
struct TYPE_4__ {int /*<<< orphan*/  io_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  wtcompare; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SEC2WTCOMP (int) ; 
 int WTCOMP2SEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 TYPE_2__ rc32434_wdt_device ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int timeout ; 
 TYPE_1__* wdt_reg ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc32434_wdt_set(int new_timeout)
{
	int max_to = WTCOMP2SEC((u32)-1);

	if (new_timeout < 0 || new_timeout > max_to) {
		pr_err("timeout value must be between 0 and %d\n", max_to);
		return -EINVAL;
	}
	timeout = new_timeout;
	spin_lock(&rc32434_wdt_device.io_lock);
	writel(SEC2WTCOMP(timeout), &wdt_reg->wtcompare);
	spin_unlock(&rc32434_wdt_device.io_lock);

	return 0;
}