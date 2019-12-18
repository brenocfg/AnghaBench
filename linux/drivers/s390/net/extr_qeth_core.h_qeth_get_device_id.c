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
struct ccw_device {int dummy; } ;
struct ccw_dev_id {int ssid; int /*<<< orphan*/  devno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_get_id (struct ccw_device*,struct ccw_dev_id*) ; 

__attribute__((used)) static inline u32 qeth_get_device_id(struct ccw_device *cdev)
{
	struct ccw_dev_id dev_id;
	u32 id;

	ccw_device_get_id(cdev, &dev_id);
	id = dev_id.devno;
	id |= (u32) (dev_id.ssid << 16);

	return id;
}