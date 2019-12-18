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
typedef  enum pvr2_config { ____Placeholder_pvr2_config } pvr2_config ;

/* Variables and functions */
#define  pvr2_config_empty 132 
#define  pvr2_config_mpeg 131 
#define  pvr2_config_pcm 130 
#define  pvr2_config_rawvideo 129 
#define  pvr2_config_vbi 128 

const char *pvr2_config_get_name(enum pvr2_config cfg)
{
	switch (cfg) {
	case pvr2_config_empty: return "empty";
	case pvr2_config_mpeg: return "mpeg";
	case pvr2_config_vbi: return "vbi";
	case pvr2_config_pcm: return "pcm";
	case pvr2_config_rawvideo: return "raw video";
	}
	return "<unknown>";
}