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
struct dw_hdmi {int /*<<< orphan*/  audio_n; int /*<<< orphan*/  audio_cts; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_set_cts_n (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_ahb_audio_enable(struct dw_hdmi *hdmi)
{
	hdmi_set_cts_n(hdmi, hdmi->audio_cts, hdmi->audio_n);
}