#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ bdRT2RTAggregation; } ;
struct rtllib_network {TYPE_1__ bssht; scalar_t__ broadcom_cap_exist; int /*<<< orphan*/  bssid; scalar_t__ ralink_cap_exist; } ;
struct rtllib_device {struct rtllib_network current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIRLINK_RALINK ; 
 int /*<<< orphan*/  BELKINF5D82334V3_RALINK ; 
 int /*<<< orphan*/  BELKINF5D8233V1_RALINK ; 
 int /*<<< orphan*/  EDIMAX_RALINK ; 
 int /*<<< orphan*/  LINKSYSWRT330_LINKSYSWRT300_BROADCOM ; 
 int /*<<< orphan*/  LINKSYSWRT350_LINKSYSWRT150_BROADCOM ; 
 int /*<<< orphan*/  PCI_RALINK ; 
 int /*<<< orphan*/  UNKNOWN_BORADCOM ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool IsHTHalfNmodeAPs(struct rtllib_device *ieee)
{
	bool			retValue = false;
	struct rtllib_network *net = &ieee->current_network;

	if ((memcmp(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
	    (memcmp(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
	    (memcmp(net->bssid, PCI_RALINK, 3) == 0) ||
	    (memcmp(net->bssid, EDIMAX_RALINK, 3) == 0) ||
	    (memcmp(net->bssid, AIRLINK_RALINK, 3) == 0) ||
	    (net->ralink_cap_exist))
		retValue = true;
	else if (!memcmp(net->bssid, UNKNOWN_BORADCOM, 3) ||
		!memcmp(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) ||
		!memcmp(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3) ||
		(net->broadcom_cap_exist))
		retValue = true;
	else if (net->bssht.bdRT2RTAggregation)
		retValue = true;
	else
		retValue = false;

	return retValue;
}