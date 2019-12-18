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
struct ccw_device {int dummy; } ;
struct ccw1 {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int ccw_device_start_timeout_key (struct ccw_device*,struct ccw1*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

int ccw_device_start_key(struct ccw_device *cdev, struct ccw1 *cpa,
			 unsigned long intparm, __u8 lpm, __u8 key,
			 unsigned long flags)
{
	return ccw_device_start_timeout_key(cdev, cpa, intparm, lpm, key,
					    flags, 0);
}