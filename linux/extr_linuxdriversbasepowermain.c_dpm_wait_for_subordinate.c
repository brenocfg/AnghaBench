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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpm_wait_for_children (struct device*,int) ; 
 int /*<<< orphan*/  dpm_wait_for_consumers (struct device*,int) ; 

__attribute__((used)) static void dpm_wait_for_subordinate(struct device *dev, bool async)
{
	dpm_wait_for_children(dev, async);
	dpm_wait_for_consumers(dev, async);
}