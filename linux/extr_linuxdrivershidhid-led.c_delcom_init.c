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
struct TYPE_4__ {int /*<<< orphan*/  family_code; } ;
struct TYPE_3__ {int cmd; } ;
union delcom_packet {TYPE_2__ fw; int /*<<< orphan*/  data; TYPE_1__ rx; } ;
struct hidled_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int hidled_recv (struct hidled_device*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delcom_init(struct hidled_device *ldev)
{
	union delcom_packet dp = { .rx.cmd = 104 };
	int ret;

	ret = hidled_recv(ldev, dp.data);
	if (ret)
		return ret;
	/*
	 * Several Delcom devices share the same USB VID/PID
	 * Check for family id 2 for Visual Signal Indicator
	 */
	return le16_to_cpu(dp.fw.family_code) == 2 ? 0 : -ENODEV;
}