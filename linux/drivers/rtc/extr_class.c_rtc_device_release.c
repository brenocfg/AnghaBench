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
struct rtc_device {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_ida ; 
 struct rtc_device* to_rtc_device (struct device*) ; 

__attribute__((used)) static void rtc_device_release(struct device *dev)
{
	struct rtc_device *rtc = to_rtc_device(dev);

	ida_simple_remove(&rtc_ida, rtc->id);
	kfree(rtc);
}