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
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpm_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dpm_wait_for_suppliers (struct device*,int) ; 

__attribute__((used)) static void dpm_wait_for_superior(struct device *dev, bool async)
{
	dpm_wait(dev->parent, async);
	dpm_wait_for_suppliers(dev, async);
}