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
typedef  int u16 ;
struct go7007 {int /*<<< orphan*/  dev; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  SPECIAL_AUDIO 139 
#define  SPECIAL_AV_SYNC 138 
#define  SPECIAL_BRC_CTRL 137 
#define  SPECIAL_CONFIG 136 
#define  SPECIAL_FINAL 135 
#define  SPECIAL_FRM_HEAD 134 
#define  SPECIAL_MODET 133 
#define  SPECIAL_SEQHEAD 132 
#define  V4L2_PIX_FMT_MJPEG 131 
#define  V4L2_PIX_FMT_MPEG1 130 
#define  V4L2_PIX_FMT_MPEG2 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int audio_to_package (struct go7007*,int /*<<< orphan*/ *,int) ; 
 int avsync_to_package (struct go7007*,int /*<<< orphan*/ *,int) ; 
 int brctrl_to_package (struct go7007*,int /*<<< orphan*/ *,int,int*) ; 
 int config_package (struct go7007*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int final_package (struct go7007*,int /*<<< orphan*/ *,int) ; 
 int gen_mjpeghdr_to_package (struct go7007*,int /*<<< orphan*/ *,int) ; 
 int gen_mpeg1hdr_to_package (struct go7007*,int /*<<< orphan*/ *,int,int*) ; 
 int gen_mpeg4hdr_to_package (struct go7007*,int /*<<< orphan*/ *,int,int*) ; 
 int modet_to_package (struct go7007*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpeg1_sequence_header ; 
 int /*<<< orphan*/  mpeg4_sequence_header ; 
 int seqhead_to_package (struct go7007*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_special(struct go7007 *go, u16 type, __le16 *code, int space,
			int *framelen)
{
	switch (type) {
	case SPECIAL_FRM_HEAD:
		switch (go->format) {
		case V4L2_PIX_FMT_MJPEG:
			return gen_mjpeghdr_to_package(go, code, space);
		case V4L2_PIX_FMT_MPEG1:
		case V4L2_PIX_FMT_MPEG2:
			return gen_mpeg1hdr_to_package(go, code, space,
								framelen);
		case V4L2_PIX_FMT_MPEG4:
			return gen_mpeg4hdr_to_package(go, code, space,
								framelen);
		default:
			break;
		}
		break;
	case SPECIAL_BRC_CTRL:
		return brctrl_to_package(go, code, space, framelen);
	case SPECIAL_CONFIG:
		return config_package(go, code, space);
	case SPECIAL_SEQHEAD:
		switch (go->format) {
		case V4L2_PIX_FMT_MPEG1:
		case V4L2_PIX_FMT_MPEG2:
			return seqhead_to_package(go, code, space,
					mpeg1_sequence_header);
		case V4L2_PIX_FMT_MPEG4:
			return seqhead_to_package(go, code, space,
					mpeg4_sequence_header);
		default:
			return 0;
		}
	case SPECIAL_AV_SYNC:
		return avsync_to_package(go, code, space);
	case SPECIAL_FINAL:
		return final_package(go, code, space);
	case SPECIAL_AUDIO:
		return audio_to_package(go, code, space);
	case SPECIAL_MODET:
		return modet_to_package(go, code, space);
	}
	dev_err(go->dev,
		"firmware file contains unsupported feature %04x\n", type);
	return -1;
}