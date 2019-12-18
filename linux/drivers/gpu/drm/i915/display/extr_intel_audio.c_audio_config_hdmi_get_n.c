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
struct intel_crtc_state {int pipe_bpp; scalar_t__ port_clock; } ;
struct hdmi_aud_ncts {int sample_rate; scalar_t__ clock; int n; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hdmi_aud_ncts*) ; 
 struct hdmi_aud_ncts* hdmi_aud_ncts_24bpp ; 
 struct hdmi_aud_ncts* hdmi_aud_ncts_30bpp ; 
 struct hdmi_aud_ncts* hdmi_aud_ncts_36bpp ; 

__attribute__((used)) static int audio_config_hdmi_get_n(const struct intel_crtc_state *crtc_state,
				   int rate)
{
	const struct hdmi_aud_ncts *hdmi_ncts_table;
	int i, size;

	if (crtc_state->pipe_bpp == 36) {
		hdmi_ncts_table = hdmi_aud_ncts_36bpp;
		size = ARRAY_SIZE(hdmi_aud_ncts_36bpp);
	} else if (crtc_state->pipe_bpp == 30) {
		hdmi_ncts_table = hdmi_aud_ncts_30bpp;
		size = ARRAY_SIZE(hdmi_aud_ncts_30bpp);
	} else {
		hdmi_ncts_table = hdmi_aud_ncts_24bpp;
		size = ARRAY_SIZE(hdmi_aud_ncts_24bpp);
	}

	for (i = 0; i < size; i++) {
		if (rate == hdmi_ncts_table[i].sample_rate &&
		    crtc_state->port_clock == hdmi_ncts_table[i].clock) {
			return hdmi_ncts_table[i].n;
		}
	}
	return 0;
}