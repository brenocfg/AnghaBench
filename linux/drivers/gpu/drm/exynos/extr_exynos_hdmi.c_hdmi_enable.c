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
struct hdmi_context {int /*<<< orphan*/  mutex; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 struct hdmi_context* encoder_to_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  hdmi_conf_apply (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmiphy_enable (struct hdmi_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_enable(struct drm_encoder *encoder)
{
	struct hdmi_context *hdata = encoder_to_hdmi(encoder);

	mutex_lock(&hdata->mutex);

	hdmiphy_enable(hdata);
	hdmi_conf_apply(hdata);

	mutex_unlock(&hdata->mutex);
}