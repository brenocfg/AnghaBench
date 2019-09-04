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
 int /*<<< orphan*/  device_for_each_child (struct device*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_wait_fn ; 

__attribute__((used)) static void dpm_wait_for_children(struct device *dev, bool async)
{
       device_for_each_child(dev, &async, dpm_wait_fn);
}