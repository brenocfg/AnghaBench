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
struct TYPE_4__ {int /*<<< orphan*/  framelen; } ;
struct TYPE_3__ {TYPE_2__ info; } ;
union hfa384x_usbin {TYPE_1__ infofrm; } ;
struct wlandevice {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prism2sta_ev_info (struct wlandevice*,TYPE_2__*) ; 

__attribute__((used)) static void hfa384x_usbin_info(struct wlandevice *wlandev,
			       union hfa384x_usbin *usbin)
{
	le16_to_cpus(&usbin->infofrm.info.framelen);
	prism2sta_ev_info(wlandev, &usbin->infofrm.info);
}