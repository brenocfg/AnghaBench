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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ps3av_pkt_audio_mode {int mask; int audio_num_of_ch; int audio_fs; int audio_word_bits; int audio_format; int audio_source; int* audio_enable; int* audio_cs_info; scalar_t__ audio_downmix_level; int /*<<< orphan*/  audio_downmix; void* audio_layout; int /*<<< orphan*/ * audio_map; int /*<<< orphan*/ * audio_swap; scalar_t__ avport; int /*<<< orphan*/  send_hdr; } ;

/* Variables and functions */
 int CS_176 ; 
 int CS_192 ; 
 int CS_44 ; 
 int CS_88 ; 
 int CS_96 ; 
 int CS_MASK ; 
 int /*<<< orphan*/  PS3AV_CID_AUDIO_MODE ; 
 int /*<<< orphan*/  PS3AV_CMD_AUDIO_DOWNMIX_PERMITTED ; 
 int PS3AV_CMD_AUDIO_FORMAT_BITSTREAM ; 
 int PS3AV_CMD_AUDIO_FORMAT_PCM ; 
#define  PS3AV_CMD_AUDIO_FS_176K 135 
#define  PS3AV_CMD_AUDIO_FS_192K 134 
#define  PS3AV_CMD_AUDIO_FS_44K 133 
 int PS3AV_CMD_AUDIO_FS_48K ; 
#define  PS3AV_CMD_AUDIO_FS_88K 132 
#define  PS3AV_CMD_AUDIO_FS_96K 131 
 void* PS3AV_CMD_AUDIO_LAYOUT_2CH ; 
 void* PS3AV_CMD_AUDIO_LAYOUT_6CH ; 
 void* PS3AV_CMD_AUDIO_LAYOUT_8CH ; 
 int /*<<< orphan*/  PS3AV_CMD_AUDIO_MAP_OUTPUT_0 ; 
 int /*<<< orphan*/  PS3AV_CMD_AUDIO_MAP_OUTPUT_1 ; 
 int /*<<< orphan*/  PS3AV_CMD_AUDIO_MAP_OUTPUT_2 ; 
 int /*<<< orphan*/  PS3AV_CMD_AUDIO_MAP_OUTPUT_3 ; 
#define  PS3AV_CMD_AUDIO_NUM_OF_CH_2 130 
#define  PS3AV_CMD_AUDIO_NUM_OF_CH_6 129 
#define  PS3AV_CMD_AUDIO_NUM_OF_CH_8 128 
 int PS3AV_CMD_AUDIO_SOURCE_SERIAL ; 
 int /*<<< orphan*/  PS3AV_CMD_AUDIO_SWAP_0 ; 
 void* PS3AV_CMD_AUDIO_WORD_BITS_16 ; 
 int PS3AV_CMD_AVPORT_HDMI_0 ; 
 int PS3AV_CMD_AVPORT_HDMI_1 ; 
 int PS3AV_CMD_AVPORT_SPDIF_0 ; 
 int PS3AV_CMD_AVPORT_SPDIF_1 ; 
 int /*<<< orphan*/  memset (struct ps3av_pkt_audio_mode*,int /*<<< orphan*/ ,int) ; 
 int* ps3av_mode_cs_info ; 
 int /*<<< orphan*/  ps3av_set_hdr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void ps3av_cmd_set_audio_mode(struct ps3av_pkt_audio_mode *audio, u32 avport,
			      u32 ch, u32 fs, u32 word_bits, u32 format,
			      u32 source)
{
	int spdif_through;
	int i;

	if (!(ch | fs | format | word_bits | source)) {
		ch = PS3AV_CMD_AUDIO_NUM_OF_CH_2;
		fs = PS3AV_CMD_AUDIO_FS_48K;
		word_bits = PS3AV_CMD_AUDIO_WORD_BITS_16;
		format = PS3AV_CMD_AUDIO_FORMAT_PCM;
		source = PS3AV_CMD_AUDIO_SOURCE_SERIAL;
	}

	/* audio mode */
	memset(audio, 0, sizeof(*audio));
	ps3av_set_hdr(PS3AV_CID_AUDIO_MODE, sizeof(*audio), &audio->send_hdr);

	audio->avport = (u8) avport;
	audio->mask = 0x0FFF;	/* XXX set all */
	audio->audio_num_of_ch = ch;
	audio->audio_fs = fs;
	audio->audio_word_bits = word_bits;
	audio->audio_format = format;
	audio->audio_source = source;

	switch (ch) {
	case PS3AV_CMD_AUDIO_NUM_OF_CH_8:
		audio->audio_enable[3] = 1;
		/* fall through */
	case PS3AV_CMD_AUDIO_NUM_OF_CH_6:
		audio->audio_enable[2] = 1;
		audio->audio_enable[1] = 1;
		/* fall through */
	case PS3AV_CMD_AUDIO_NUM_OF_CH_2:
	default:
		audio->audio_enable[0] = 1;
	}

	/* audio swap L/R */
	for (i = 0; i < 4; i++)
		audio->audio_swap[i] = PS3AV_CMD_AUDIO_SWAP_0;	/* no swap */

	/* audio serial input mapping */
	audio->audio_map[0] = PS3AV_CMD_AUDIO_MAP_OUTPUT_0;
	audio->audio_map[1] = PS3AV_CMD_AUDIO_MAP_OUTPUT_1;
	audio->audio_map[2] = PS3AV_CMD_AUDIO_MAP_OUTPUT_2;
	audio->audio_map[3] = PS3AV_CMD_AUDIO_MAP_OUTPUT_3;

	/* audio speaker layout */
	if (avport == PS3AV_CMD_AVPORT_HDMI_0 ||
	    avport == PS3AV_CMD_AVPORT_HDMI_1) {
		switch (ch) {
		case PS3AV_CMD_AUDIO_NUM_OF_CH_8:
			audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_8CH;
			break;
		case PS3AV_CMD_AUDIO_NUM_OF_CH_6:
			audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_6CH;
			break;
		case PS3AV_CMD_AUDIO_NUM_OF_CH_2:
		default:
			audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_2CH;
			break;
		}
	} else {
		audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_2CH;
	}

	/* audio downmix permission */
	audio->audio_downmix = PS3AV_CMD_AUDIO_DOWNMIX_PERMITTED;
	/* audio downmix level shift (0:0dB to 15:15dB) */
	audio->audio_downmix_level = 0;	/* 0dB */

	/* set ch status */
	for (i = 0; i < 8; i++)
		audio->audio_cs_info[i] = ps3av_mode_cs_info[i];

	switch (fs) {
	case PS3AV_CMD_AUDIO_FS_44K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_44;
		break;
	case PS3AV_CMD_AUDIO_FS_88K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_88;
		break;
	case PS3AV_CMD_AUDIO_FS_96K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_96;
		break;
	case PS3AV_CMD_AUDIO_FS_176K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_176;
		break;
	case PS3AV_CMD_AUDIO_FS_192K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_192;
		break;
	default:
		break;
	}

	/* non-audio bit */
	spdif_through = audio->audio_cs_info[0] & 0x02;

	/* pass through setting */
	if (spdif_through &&
	    (avport == PS3AV_CMD_AVPORT_SPDIF_0 ||
	     avport == PS3AV_CMD_AVPORT_SPDIF_1 ||
	     avport == PS3AV_CMD_AVPORT_HDMI_0 ||
	     avport == PS3AV_CMD_AVPORT_HDMI_1)) {
		audio->audio_word_bits = PS3AV_CMD_AUDIO_WORD_BITS_16;
		audio->audio_format = PS3AV_CMD_AUDIO_FORMAT_BITSTREAM;
	}
}