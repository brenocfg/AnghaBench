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
struct TYPE_4__ {int /*<<< orphan*/  data; TYPE_1__* ops; } ;
struct dw_hdmi {TYPE_2__ phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_hpd ) (struct dw_hdmi*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_i2c_init (struct dw_hdmi*) ; 
 int /*<<< orphan*/  initialize_hdmi_ih_mutes (struct dw_hdmi*) ; 
 int /*<<< orphan*/  stub1 (struct dw_hdmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_init_hw(struct dw_hdmi *hdmi)
{
	initialize_hdmi_ih_mutes(hdmi);

	/*
	 * Reset HDMI DDC I2C master controller and mute I2CM interrupts.
	 * Even if we are using a separate i2c adapter doing this doesn't
	 * hurt.
	 */
	dw_hdmi_i2c_init(hdmi);

	if (hdmi->phy.ops->setup_hpd)
		hdmi->phy.ops->setup_hpd(hdmi, hdmi->phy.data);
}