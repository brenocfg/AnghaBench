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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ mdataenablepolarity; } ;
struct TYPE_4__ {TYPE_1__ video_mode; } ;
struct dw_hdmi {TYPE_2__ hdmi_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_A_HDCPCFG0 ; 
 int /*<<< orphan*/  HDMI_A_HDCPCFG0_RXDETECT_DISABLE ; 
 int /*<<< orphan*/  HDMI_A_HDCPCFG0_RXDETECT_MASK ; 
 int /*<<< orphan*/  HDMI_A_HDCPCFG1 ; 
 int /*<<< orphan*/  HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_DISABLE ; 
 int /*<<< orphan*/  HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_MASK ; 
 int /*<<< orphan*/  HDMI_A_VIDPOLCFG ; 
 int /*<<< orphan*/  HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH ; 
 int /*<<< orphan*/  HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_LOW ; 
 int /*<<< orphan*/  HDMI_A_VIDPOLCFG_DATAENPOL_MASK ; 
 int /*<<< orphan*/  hdmi_modb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_tx_hdcp_config(struct dw_hdmi *hdmi)
{
	u8 de;

	if (hdmi->hdmi_data.video_mode.mdataenablepolarity)
		de = HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH;
	else
		de = HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_LOW;

	/* disable rx detect */
	hdmi_modb(hdmi, HDMI_A_HDCPCFG0_RXDETECT_DISABLE,
		  HDMI_A_HDCPCFG0_RXDETECT_MASK, HDMI_A_HDCPCFG0);

	hdmi_modb(hdmi, de, HDMI_A_VIDPOLCFG_DATAENPOL_MASK, HDMI_A_VIDPOLCFG);

	hdmi_modb(hdmi, HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_DISABLE,
		  HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_MASK, HDMI_A_HDCPCFG1);
}