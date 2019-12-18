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
struct dw_hdmi {int /*<<< orphan*/  audio_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_FC_AUDICONF2 ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dw_hdmi_set_channel_allocation(struct dw_hdmi *hdmi, unsigned int ca)
{
	mutex_lock(&hdmi->audio_mutex);

	hdmi_writeb(hdmi, ca, HDMI_FC_AUDICONF2);

	mutex_unlock(&hdmi->audio_mutex);
}