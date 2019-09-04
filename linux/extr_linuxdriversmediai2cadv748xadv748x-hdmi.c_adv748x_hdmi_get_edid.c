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
struct v4l2_edid {scalar_t__ start_block; scalar_t__ blocks; int /*<<< orphan*/  edid; int /*<<< orphan*/  reserved; } ;
struct TYPE_2__ {scalar_t__ blocks; scalar_t__ edid; int /*<<< orphan*/  present; } ;
struct adv748x_hdmi {TYPE_1__ edid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 struct adv748x_hdmi* adv748x_sd_to_hdmi (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adv748x_hdmi_get_edid(struct v4l2_subdev *sd, struct v4l2_edid *edid)
{
	struct adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);

	memset(edid->reserved, 0, sizeof(edid->reserved));

	if (!hdmi->edid.present)
		return -ENODATA;

	if (edid->start_block == 0 && edid->blocks == 0) {
		edid->blocks = hdmi->edid.blocks;
		return 0;
	}

	if (edid->start_block >= hdmi->edid.blocks)
		return -EINVAL;

	if (edid->start_block + edid->blocks > hdmi->edid.blocks)
		edid->blocks = hdmi->edid.blocks - edid->start_block;

	memcpy(edid->edid, hdmi->edid.edid + edid->start_block * 128,
			edid->blocks * 128);

	return 0;
}