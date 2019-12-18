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
struct rtllib_device {int softmac_features; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* start_send_beacons ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_BEACONS ; 
 int /*<<< orphan*/  rtllib_beacons_start (struct rtllib_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void rtllib_start_send_beacons(struct rtllib_device *ieee)
{
	if (ieee->start_send_beacons)
		ieee->start_send_beacons(ieee->dev);
	if (ieee->softmac_features & IEEE_SOFTMAC_BEACONS)
		rtllib_beacons_start(ieee);
}