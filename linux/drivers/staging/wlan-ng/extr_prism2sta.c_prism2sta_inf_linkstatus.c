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
struct wlandevice {struct hfa384x* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  linkstatus; } ;
struct TYPE_4__ {TYPE_1__ linkstatus; } ;
struct hfa384x_inf_frame {TYPE_2__ info; } ;
struct hfa384x {int /*<<< orphan*/  link_bh; int /*<<< orphan*/  link_status_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prism2sta_inf_linkstatus(struct wlandevice *wlandev,
				     struct hfa384x_inf_frame *inf)
{
	struct hfa384x *hw = wlandev->priv;

	hw->link_status_new = le16_to_cpu(inf->info.linkstatus.linkstatus);

	schedule_work(&hw->link_bh);
}