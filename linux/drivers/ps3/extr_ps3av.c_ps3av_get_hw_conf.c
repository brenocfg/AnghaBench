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
struct ps3av_pkt_av_get_hw_conf {int num_of_hdmi; int num_of_avmulti; int num_of_spdif; } ;
struct ps3av {int audio_port; void** av_port; void** opt_port; scalar_t__* head; struct ps3av_pkt_av_get_hw_conf av_hw_conf; } ;

/* Variables and functions */
 int PS3AV_CMD_AUDIO_PORT_AVMULTI_0 ; 
 int PS3AV_CMD_AUDIO_PORT_HDMI_0 ; 
 int PS3AV_CMD_AUDIO_PORT_HDMI_1 ; 
 int PS3AV_CMD_AUDIO_PORT_SPDIF_0 ; 
 int PS3AV_CMD_AUDIO_PORT_SPDIF_1 ; 
 void* PS3AV_CMD_AVPORT_AVMULTI_0 ; 
 void* PS3AV_CMD_AVPORT_HDMI_0 ; 
 void* PS3AV_CMD_AVPORT_SPDIF_0 ; 
 scalar_t__ PS3AV_CMD_VIDEO_HEAD_A ; 
 int PS3AV_HEAD_MAX ; 
 int PS3AV_OPT_PORT_MAX ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int ps3av_cmd_av_get_hw_conf (struct ps3av_pkt_av_get_hw_conf*) ; 

__attribute__((used)) static int ps3av_get_hw_conf(struct ps3av *ps3av)
{
	int i, j, k, res;
	const struct ps3av_pkt_av_get_hw_conf *hw_conf;

	/* get av_hw_conf */
	res = ps3av_cmd_av_get_hw_conf(&ps3av->av_hw_conf);
	if (res < 0)
		return -1;

	hw_conf = &ps3av->av_hw_conf;
	pr_debug("av_h_conf: num of hdmi: %u\n", hw_conf->num_of_hdmi);
	pr_debug("av_h_conf: num of avmulti: %u\n", hw_conf->num_of_avmulti);
	pr_debug("av_h_conf: num of spdif: %u\n", hw_conf->num_of_spdif);

	for (i = 0; i < PS3AV_HEAD_MAX; i++)
		ps3av->head[i] = PS3AV_CMD_VIDEO_HEAD_A + i;
	for (i = 0; i < PS3AV_OPT_PORT_MAX; i++)
		ps3av->opt_port[i] = PS3AV_CMD_AVPORT_SPDIF_0 + i;
	for (i = 0; i < hw_conf->num_of_hdmi; i++)
		ps3av->av_port[i] = PS3AV_CMD_AVPORT_HDMI_0 + i;
	for (j = 0; j < hw_conf->num_of_avmulti; j++)
		ps3av->av_port[i + j] = PS3AV_CMD_AVPORT_AVMULTI_0 + j;
	for (k = 0; k < hw_conf->num_of_spdif; k++)
		ps3av->av_port[i + j + k] = PS3AV_CMD_AVPORT_SPDIF_0 + k;

	/* set all audio port */
	ps3av->audio_port = PS3AV_CMD_AUDIO_PORT_HDMI_0
	    | PS3AV_CMD_AUDIO_PORT_HDMI_1
	    | PS3AV_CMD_AUDIO_PORT_AVMULTI_0
	    | PS3AV_CMD_AUDIO_PORT_SPDIF_0 | PS3AV_CMD_AUDIO_PORT_SPDIF_1;

	return 0;
}