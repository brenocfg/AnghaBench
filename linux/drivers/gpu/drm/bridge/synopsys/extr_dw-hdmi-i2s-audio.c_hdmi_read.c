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
typedef  int /*<<< orphan*/  u8 ;
struct dw_hdmi_i2s_audio_data {int /*<<< orphan*/  (* read ) (struct dw_hdmi*,int) ;struct dw_hdmi* hdmi; } ;
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dw_hdmi*,int) ; 

__attribute__((used)) static inline u8 hdmi_read(struct dw_hdmi_i2s_audio_data *audio, int offset)
{
	struct dw_hdmi *hdmi = audio->hdmi;

	return audio->read(hdmi, offset);
}