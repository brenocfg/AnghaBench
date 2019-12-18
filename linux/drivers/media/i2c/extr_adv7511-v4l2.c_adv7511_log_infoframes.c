#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; } ;
struct adv7511_cfg_read_infoframe {char* member_0; int member_1; int member_2; int member_4; TYPE_1__ member_3; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct adv7511_cfg_read_infoframe const*) ; 
 int /*<<< orphan*/  log_infoframe (struct v4l2_subdev*,struct adv7511_cfg_read_infoframe const*) ; 

__attribute__((used)) static void adv7511_log_infoframes(struct v4l2_subdev *sd)
{
	static const struct adv7511_cfg_read_infoframe cri[] = {
		{ "AVI", 0x44, 0x10, { 0x82, 2, 13 }, 0x55 },
		{ "Audio", 0x44, 0x08, { 0x84, 1, 10 }, 0x73 },
		{ "SDP", 0x40, 0x40, { 0x83, 1, 25 }, 0x103 },
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(cri); i++)
		log_infoframe(sd, &cri[i]);
}