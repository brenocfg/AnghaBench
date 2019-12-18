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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int aud_input; struct v4l2_subdev sd; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_INFO_DEV (struct v4l2_subdev*,char*,...) ; 
 int cx18_av_read (struct cx18*,int) ; 

__attribute__((used)) static void log_audio_status(struct cx18 *cx)
{
	struct cx18_av_state *state = &cx->av_state;
	struct v4l2_subdev *sd = &state->sd;
	u8 download_ctl = cx18_av_read(cx, 0x803);
	u8 mod_det_stat0 = cx18_av_read(cx, 0x804);
	u8 mod_det_stat1 = cx18_av_read(cx, 0x805);
	u8 audio_config = cx18_av_read(cx, 0x808);
	u8 pref_mode = cx18_av_read(cx, 0x809);
	u8 afc0 = cx18_av_read(cx, 0x80b);
	u8 mute_ctl = cx18_av_read(cx, 0x8d3);
	int aud_input = state->aud_input;
	char *p;

	switch (mod_det_stat0) {
	case 0x00: p = "mono"; break;
	case 0x01: p = "stereo"; break;
	case 0x02: p = "dual"; break;
	case 0x04: p = "tri"; break;
	case 0x10: p = "mono with SAP"; break;
	case 0x11: p = "stereo with SAP"; break;
	case 0x12: p = "dual with SAP"; break;
	case 0x14: p = "tri with SAP"; break;
	case 0xfe: p = "forced mode"; break;
	default: p = "not defined"; break;
	}
	CX18_INFO_DEV(sd, "Detected audio mode:       %s\n", p);

	switch (mod_det_stat1) {
	case 0x00: p = "not defined"; break;
	case 0x01: p = "EIAJ"; break;
	case 0x02: p = "A2-M"; break;
	case 0x03: p = "A2-BG"; break;
	case 0x04: p = "A2-DK1"; break;
	case 0x05: p = "A2-DK2"; break;
	case 0x06: p = "A2-DK3"; break;
	case 0x07: p = "A1 (6.0 MHz FM Mono)"; break;
	case 0x08: p = "AM-L"; break;
	case 0x09: p = "NICAM-BG"; break;
	case 0x0a: p = "NICAM-DK"; break;
	case 0x0b: p = "NICAM-I"; break;
	case 0x0c: p = "NICAM-L"; break;
	case 0x0d: p = "BTSC/EIAJ/A2-M Mono (4.5 MHz FMMono)"; break;
	case 0x0e: p = "IF FM Radio"; break;
	case 0x0f: p = "BTSC"; break;
	case 0x10: p = "detected chrominance"; break;
	case 0xfd: p = "unknown audio standard"; break;
	case 0xfe: p = "forced audio standard"; break;
	case 0xff: p = "no detected audio standard"; break;
	default: p = "not defined"; break;
	}
	CX18_INFO_DEV(sd, "Detected audio standard:   %s\n", p);
	CX18_INFO_DEV(sd, "Audio muted:               %s\n",
		      (mute_ctl & 0x2) ? "yes" : "no");
	CX18_INFO_DEV(sd, "Audio microcontroller:     %s\n",
		      (download_ctl & 0x10) ? "running" : "stopped");

	switch (audio_config >> 4) {
	case 0x00: p = "undefined"; break;
	case 0x01: p = "BTSC"; break;
	case 0x02: p = "EIAJ"; break;
	case 0x03: p = "A2-M"; break;
	case 0x04: p = "A2-BG"; break;
	case 0x05: p = "A2-DK1"; break;
	case 0x06: p = "A2-DK2"; break;
	case 0x07: p = "A2-DK3"; break;
	case 0x08: p = "A1 (6.0 MHz FM Mono)"; break;
	case 0x09: p = "AM-L"; break;
	case 0x0a: p = "NICAM-BG"; break;
	case 0x0b: p = "NICAM-DK"; break;
	case 0x0c: p = "NICAM-I"; break;
	case 0x0d: p = "NICAM-L"; break;
	case 0x0e: p = "FM radio"; break;
	case 0x0f: p = "automatic detection"; break;
	default: p = "undefined"; break;
	}
	CX18_INFO_DEV(sd, "Configured audio standard: %s\n", p);

	if ((audio_config >> 4) < 0xF) {
		switch (audio_config & 0xF) {
		case 0x00: p = "MONO1 (LANGUAGE A/Mono L+R channel for BTSC, EIAJ, A2)"; break;
		case 0x01: p = "MONO2 (LANGUAGE B)"; break;
		case 0x02: p = "MONO3 (STEREO forced MONO)"; break;
		case 0x03: p = "MONO4 (NICAM ANALOG-Language C/Analog Fallback)"; break;
		case 0x04: p = "STEREO"; break;
		case 0x05: p = "DUAL1 (AC)"; break;
		case 0x06: p = "DUAL2 (BC)"; break;
		case 0x07: p = "DUAL3 (AB)"; break;
		default: p = "undefined";
		}
		CX18_INFO_DEV(sd, "Configured audio mode:     %s\n", p);
	} else {
		switch (audio_config & 0xF) {
		case 0x00: p = "BG"; break;
		case 0x01: p = "DK1"; break;
		case 0x02: p = "DK2"; break;
		case 0x03: p = "DK3"; break;
		case 0x04: p = "I"; break;
		case 0x05: p = "L"; break;
		case 0x06: p = "BTSC"; break;
		case 0x07: p = "EIAJ"; break;
		case 0x08: p = "A2-M"; break;
		case 0x09: p = "FM Radio (4.5 MHz)"; break;
		case 0x0a: p = "FM Radio (5.5 MHz)"; break;
		case 0x0b: p = "S-Video"; break;
		case 0x0f: p = "automatic standard and mode detection"; break;
		default: p = "undefined"; break;
		}
		CX18_INFO_DEV(sd, "Configured audio system:   %s\n", p);
	}

	if (aud_input)
		CX18_INFO_DEV(sd, "Specified audio input:     Tuner (In%d)\n",
			      aud_input);
	else
		CX18_INFO_DEV(sd, "Specified audio input:     External\n");

	switch (pref_mode & 0xf) {
	case 0: p = "mono/language A"; break;
	case 1: p = "language B"; break;
	case 2: p = "language C"; break;
	case 3: p = "analog fallback"; break;
	case 4: p = "stereo"; break;
	case 5: p = "language AC"; break;
	case 6: p = "language BC"; break;
	case 7: p = "language AB"; break;
	default: p = "undefined"; break;
	}
	CX18_INFO_DEV(sd, "Preferred audio mode:      %s\n", p);

	if ((audio_config & 0xf) == 0xf) {
		switch ((afc0 >> 3) & 0x1) {
		case 0: p = "system DK"; break;
		case 1: p = "system L"; break;
		}
		CX18_INFO_DEV(sd, "Selected 65 MHz format:    %s\n", p);

		switch (afc0 & 0x7) {
		case 0: p = "Chroma"; break;
		case 1: p = "BTSC"; break;
		case 2: p = "EIAJ"; break;
		case 3: p = "A2-M"; break;
		case 4: p = "autodetect"; break;
		default: p = "undefined"; break;
		}
		CX18_INFO_DEV(sd, "Selected 45 MHz format:    %s\n", p);
	}
}