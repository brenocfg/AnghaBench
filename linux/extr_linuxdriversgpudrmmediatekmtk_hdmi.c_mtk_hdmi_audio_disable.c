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
struct mtk_hdmi {int audio_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_hdmi_aud_enable_packet (struct mtk_hdmi*,int) ; 

__attribute__((used)) static void mtk_hdmi_audio_disable(struct mtk_hdmi *hdmi)
{
	mtk_hdmi_aud_enable_packet(hdmi, false);
	hdmi->audio_enable = false;
}