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
struct TYPE_4__ {int enabled; int /*<<< orphan*/  data; TYPE_1__* ops; } ;
struct dw_hdmi {int bridge_is_on; TYPE_2__ phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable ) (struct dw_hdmi*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dw_hdmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_poweroff(struct dw_hdmi *hdmi)
{
	if (hdmi->phy.enabled) {
		hdmi->phy.ops->disable(hdmi, hdmi->phy.data);
		hdmi->phy.enabled = false;
	}

	hdmi->bridge_is_on = false;
}