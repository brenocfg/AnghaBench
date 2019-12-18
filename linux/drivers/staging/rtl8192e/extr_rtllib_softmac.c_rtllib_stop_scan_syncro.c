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
struct rtllib_device {int softmac_features; int sync_scan_hurryup; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* rtllib_stop_hw_scan ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_SCAN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void rtllib_stop_scan_syncro(struct rtllib_device *ieee)
{
	if (ieee->softmac_features & IEEE_SOFTMAC_SCAN) {
		ieee->sync_scan_hurryup = 1;
	} else {
		if (ieee->rtllib_stop_hw_scan)
			ieee->rtllib_stop_hw_scan(ieee->dev);
	}
}