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
struct stm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct stm_device* to_stm_device (struct device*) ; 
 int /*<<< orphan*/  vfree (struct stm_device*) ; 

__attribute__((used)) static void stm_device_release(struct device *dev)
{
	struct stm_device *stm = to_stm_device(dev);

	vfree(stm);
}