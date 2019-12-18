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
struct mii_if_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int mii_link_ok (struct mii_if_info*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

void mii_check_link (struct mii_if_info *mii)
{
	int cur_link = mii_link_ok(mii);
	int prev_link = netif_carrier_ok(mii->dev);

	if (cur_link && !prev_link)
		netif_carrier_on(mii->dev);
	else if (prev_link && !cur_link)
		netif_carrier_off(mii->dev);
}