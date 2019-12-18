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
struct omap_hdmi {int /*<<< orphan*/  wp; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi4_audio_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_wp_audio_enable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hdmi_stop_audio_stream(struct omap_hdmi *hd)
{
	hdmi4_audio_stop(&hd->core, &hd->wp);
	hdmi_wp_audio_enable(&hd->wp, false);
}