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
struct v4l2_subdev {int dummy; } ;
struct adv7842_cfg_read_infoframe {char* member_0; int member_1; int member_2; int member_3; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct adv7842_cfg_read_infoframe*) ; 
 int hdmi_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  log_infoframe (struct v4l2_subdev*,struct adv7842_cfg_read_infoframe*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static void adv7842_log_infoframes(struct v4l2_subdev *sd)
{
	int i;
	struct adv7842_cfg_read_infoframe cri[] = {
		{ "AVI", 0x01, 0xe0, 0x00 },
		{ "Audio", 0x02, 0xe3, 0x1c },
		{ "SDP", 0x04, 0xe6, 0x2a },
		{ "Vendor", 0x10, 0xec, 0x54 }
	};

	if (!(hdmi_read(sd, 0x05) & 0x80)) {
		v4l2_info(sd, "receive DVI-D signal, no infoframes\n");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(cri); i++)
		log_infoframe(sd, &cri[i]);
}