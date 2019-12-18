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
struct dw_hdmi_i2s_audio_data {struct dw_hdmi* hdmi; } ;
struct dw_hdmi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_audio_disable (struct dw_hdmi*) ; 

__attribute__((used)) static void dw_hdmi_i2s_audio_shutdown(struct device *dev, void *data)
{
	struct dw_hdmi_i2s_audio_data *audio = data;
	struct dw_hdmi *hdmi = audio->hdmi;

	dw_hdmi_audio_disable(hdmi);
}