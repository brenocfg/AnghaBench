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
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AUD_CTS1 ; 
 int /*<<< orphan*/  HDMI_AUD_CTS2 ; 
 int /*<<< orphan*/  HDMI_AUD_CTS3 ; 
 unsigned int HDMI_AUD_CTS3_AUDCTS19_16_MASK ; 
 unsigned int HDMI_AUD_CTS3_CTS_MANUAL ; 
 unsigned int HDMI_AUD_CTS3_N_SHIFT_MASK ; 
 int /*<<< orphan*/  HDMI_AUD_N1 ; 
 int /*<<< orphan*/  HDMI_AUD_N2 ; 
 int /*<<< orphan*/  HDMI_AUD_N3 ; 
 int /*<<< orphan*/  hdmi_modb (struct dw_hdmi*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_set_cts_n(struct dw_hdmi *hdmi, unsigned int cts,
			   unsigned int n)
{
	/* Must be set/cleared first */
	hdmi_modb(hdmi, 0, HDMI_AUD_CTS3_CTS_MANUAL, HDMI_AUD_CTS3);

	/* nshift factor = 0 */
	hdmi_modb(hdmi, 0, HDMI_AUD_CTS3_N_SHIFT_MASK, HDMI_AUD_CTS3);

	/* Use automatic CTS generation mode when CTS is not set */
	if (cts)
		hdmi_writeb(hdmi, ((cts >> 16) &
				   HDMI_AUD_CTS3_AUDCTS19_16_MASK) |
				  HDMI_AUD_CTS3_CTS_MANUAL,
			    HDMI_AUD_CTS3);
	else
		hdmi_writeb(hdmi, 0, HDMI_AUD_CTS3);
	hdmi_writeb(hdmi, (cts >> 8) & 0xff, HDMI_AUD_CTS2);
	hdmi_writeb(hdmi, cts & 0xff, HDMI_AUD_CTS1);

	hdmi_writeb(hdmi, (n >> 16) & 0x0f, HDMI_AUD_N3);
	hdmi_writeb(hdmi, (n >> 8) & 0xff, HDMI_AUD_N2);
	hdmi_writeb(hdmi, n & 0xff, HDMI_AUD_N1);
}