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
typedef  int /*<<< orphan*/  u32 ;
struct ci_hdrc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OTGSC_BSV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hw_read_otgsc (struct ci_hdrc*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int hw_wait_vbus_lower_bsv(struct ci_hdrc *ci)
{
	unsigned long elapse = jiffies + msecs_to_jiffies(5000);
	u32 mask = OTGSC_BSV;

	while (hw_read_otgsc(ci, mask)) {
		if (time_after(jiffies, elapse)) {
			dev_err(ci->dev, "timeout waiting for %08x in OTGSC\n",
					mask);
			return -ETIMEDOUT;
		}
		msleep(20);
	}

	return 0;
}