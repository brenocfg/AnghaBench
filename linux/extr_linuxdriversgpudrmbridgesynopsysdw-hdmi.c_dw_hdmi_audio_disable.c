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
struct dw_hdmi {int audio_enable; int /*<<< orphan*/  audio_lock; int /*<<< orphan*/  (* disable_audio ) (struct dw_hdmi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dw_hdmi*) ; 

void dw_hdmi_audio_disable(struct dw_hdmi *hdmi)
{
	unsigned long flags;

	spin_lock_irqsave(&hdmi->audio_lock, flags);
	hdmi->audio_enable = false;
	if (hdmi->disable_audio)
		hdmi->disable_audio(hdmi);
	spin_unlock_irqrestore(&hdmi->audio_lock, flags);
}