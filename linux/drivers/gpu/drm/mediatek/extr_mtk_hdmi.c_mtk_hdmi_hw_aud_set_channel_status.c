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
struct mtk_hdmi {int dummy; } ;

/* Variables and functions */
 scalar_t__ GRL_I2S_C_STA0 ; 
 scalar_t__ GRL_L_STATUS_0 ; 
 scalar_t__ GRL_R_STATUS_0 ; 
 int /*<<< orphan*/  mtk_hdmi_write (struct mtk_hdmi*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_set_channel_status(struct mtk_hdmi *hdmi,
					       u8 *channel_status)
{
	int i;

	for (i = 0; i < 5; i++) {
		mtk_hdmi_write(hdmi, GRL_I2S_C_STA0 + i * 4, channel_status[i]);
		mtk_hdmi_write(hdmi, GRL_L_STATUS_0 + i * 4, channel_status[i]);
		mtk_hdmi_write(hdmi, GRL_R_STATUS_0 + i * 4, channel_status[i]);
	}
	for (; i < 24; i++) {
		mtk_hdmi_write(hdmi, GRL_L_STATUS_0 + i * 4, 0);
		mtk_hdmi_write(hdmi, GRL_R_STATUS_0 + i * 4, 0);
	}
}