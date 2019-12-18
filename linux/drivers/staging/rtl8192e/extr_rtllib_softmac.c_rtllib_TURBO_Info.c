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
typedef  int /*<<< orphan*/  u8 ;
struct rtllib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFIE_TYPE_GENERIC ; 
 int /*<<< orphan*/  netdev_alert (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void rtllib_TURBO_Info(struct rtllib_device *ieee, u8 **tag_p)
{
	u8 *tag = *tag_p;

	*tag++ = MFIE_TYPE_GENERIC;
	*tag++ = 7;
	*tag++ = 0x00;
	*tag++ = 0xe0;
	*tag++ = 0x4c;
	*tag++ = 0x01;
	*tag++ = 0x02;
	*tag++ = 0x11;
	*tag++ = 0x00;

	*tag_p = tag;
	netdev_alert(ieee->dev, "This is enable turbo mode IE process\n");
}