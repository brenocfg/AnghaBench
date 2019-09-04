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
struct dw_hdmi {int bridge_is_on; int /*<<< orphan*/  previous_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_setup (struct dw_hdmi*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_hdmi_poweron(struct dw_hdmi *hdmi)
{
	hdmi->bridge_is_on = true;
	dw_hdmi_setup(hdmi, &hdmi->previous_mode);
}