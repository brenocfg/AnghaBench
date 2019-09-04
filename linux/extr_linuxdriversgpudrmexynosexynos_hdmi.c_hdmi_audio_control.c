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
struct TYPE_2__ {int /*<<< orphan*/  mute; } ;
struct hdmi_context {scalar_t__ dvi_mode; TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_ASP_DIS ; 
 int /*<<< orphan*/  HDMI_ASP_EN ; 
 int /*<<< orphan*/  HDMI_ASP_MASK ; 
 int /*<<< orphan*/  HDMI_AUI_CON ; 
 int /*<<< orphan*/  HDMI_AUI_CON_NO_TRAN ; 
 int /*<<< orphan*/  HDMI_AVI_CON_EVERY_VSYNC ; 
 int /*<<< orphan*/  HDMI_CON_0 ; 
 int /*<<< orphan*/  hdmi_reg_writeb (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_reg_writemask (struct hdmi_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_audio_control(struct hdmi_context *hdata)
{
	bool enable = !hdata->audio.mute;

	if (hdata->dvi_mode)
		return;

	hdmi_reg_writeb(hdata, HDMI_AUI_CON, enable ?
			HDMI_AVI_CON_EVERY_VSYNC : HDMI_AUI_CON_NO_TRAN);
	hdmi_reg_writemask(hdata, HDMI_CON_0, enable ?
			HDMI_ASP_EN : HDMI_ASP_DIS, HDMI_ASP_MASK);
}