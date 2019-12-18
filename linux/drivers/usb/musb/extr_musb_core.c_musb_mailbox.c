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
typedef  enum musb_vbus_id_status { ____Placeholder_musb_vbus_id_status } musb_vbus_id_status ;

/* Variables and functions */
 int ENODEV ; 
 int musb_phy_callback (int) ; 

int musb_mailbox(enum musb_vbus_id_status status)
{
	if (musb_phy_callback)
		return musb_phy_callback(status);

	return -ENODEV;
}