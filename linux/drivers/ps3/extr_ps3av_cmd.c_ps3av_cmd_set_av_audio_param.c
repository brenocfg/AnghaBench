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
typedef  int u32 ;
struct ps3av_pkt_av_audio_param {int avport; int mclk; int swaplr; int inputctrl; int /*<<< orphan*/  chstat; int /*<<< orphan*/  info; int /*<<< orphan*/  layout; int /*<<< orphan*/  inputlen; int /*<<< orphan*/  fifomap; int /*<<< orphan*/  enable; int /*<<< orphan*/  ns; int /*<<< orphan*/  send_hdr; } ;
struct ps3av_pkt_audio_mode {int /*<<< orphan*/  audio_cs_info; int /*<<< orphan*/  audio_num_of_ch; int /*<<< orphan*/  audio_word_bits; int /*<<< orphan*/  audio_map; int /*<<< orphan*/  audio_enable; int /*<<< orphan*/  audio_source; int /*<<< orphan*/  audio_fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3AV_CID_AV_AUDIO_PARAM ; 
 int /*<<< orphan*/  memset (struct ps3av_pkt_av_audio_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps3av_cnv_chstat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_cnv_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_cnv_fifomap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_cnv_info (int /*<<< orphan*/ *,struct ps3av_pkt_audio_mode const*) ; 
 int /*<<< orphan*/  ps3av_cnv_inputlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_cnv_layout (int /*<<< orphan*/ ) ; 
 int ps3av_cnv_mclk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_cnv_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps3av_set_hdr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

u32 ps3av_cmd_set_av_audio_param(void *p, u32 port,
				 const struct ps3av_pkt_audio_mode *audio_mode,
				 u32 video_vid)
{
	struct ps3av_pkt_av_audio_param *param;

	param = (struct ps3av_pkt_av_audio_param *)p;

	memset(param, 0, sizeof(*param));
	ps3av_set_hdr(PS3AV_CID_AV_AUDIO_PARAM, sizeof(*param),
		      &param->send_hdr);

	param->avport = port;
	param->mclk = ps3av_cnv_mclk(audio_mode->audio_fs) | 0x80;
	ps3av_cnv_ns(param->ns, audio_mode->audio_fs, video_vid);
	param->enable = ps3av_cnv_enable(audio_mode->audio_source,
					 audio_mode->audio_enable);
	param->swaplr = 0x09;
	param->fifomap = ps3av_cnv_fifomap(audio_mode->audio_map);
	param->inputctrl = 0x49;
	param->inputlen = ps3av_cnv_inputlen(audio_mode->audio_word_bits);
	param->layout = ps3av_cnv_layout(audio_mode->audio_num_of_ch);
	ps3av_cnv_info(&param->info, audio_mode);
	ps3av_cnv_chstat(param->chstat, audio_mode->audio_cs_info);

	return sizeof(*param);
}