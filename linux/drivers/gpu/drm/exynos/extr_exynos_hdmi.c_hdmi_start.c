#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {TYPE_2__* crtc; } ;
struct hdmi_context {TYPE_3__ encoder; } ;
struct drm_display_mode {int flags; } ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_4__ {struct drm_display_mode mode; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HDMI_CON_0 ; 
 int HDMI_EN ; 
 int HDMI_FIELD_EN ; 
 int /*<<< orphan*/  HDMI_TG_CMD ; 
 int HDMI_TG_EN ; 
 int /*<<< orphan*/  hdmi_reg_writemask (struct hdmi_context*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hdmi_start(struct hdmi_context *hdata, bool start)
{
	struct drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	u32 val = start ? HDMI_TG_EN : 0;

	if (m->flags & DRM_MODE_FLAG_INTERLACE)
		val |= HDMI_FIELD_EN;

	hdmi_reg_writemask(hdata, HDMI_CON_0, val, HDMI_EN);
	hdmi_reg_writemask(hdata, HDMI_TG_CMD, val, HDMI_TG_EN | HDMI_FIELD_EN);
}