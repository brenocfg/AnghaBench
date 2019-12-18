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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_edid {int pad; scalar_t__ start_block; scalar_t__ blocks; int /*<<< orphan*/  edid; int /*<<< orphan*/  reserved; } ;
struct TYPE_2__ {int present; scalar_t__ blocks; int /*<<< orphan*/ * edid; } ;
struct adv76xx_state {TYPE_1__ edid; } ;

/* Variables and functions */
#define  ADV7604_PAD_HDMI_PORT_B 131 
#define  ADV7604_PAD_HDMI_PORT_C 130 
#define  ADV7604_PAD_HDMI_PORT_D 129 
#define  ADV76XX_PAD_HDMI_PORT_A 128 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv76xx_get_edid(struct v4l2_subdev *sd, struct v4l2_edid *edid)
{
	struct adv76xx_state *state = to_state(sd);
	u8 *data = NULL;

	memset(edid->reserved, 0, sizeof(edid->reserved));

	switch (edid->pad) {
	case ADV76XX_PAD_HDMI_PORT_A:
	case ADV7604_PAD_HDMI_PORT_B:
	case ADV7604_PAD_HDMI_PORT_C:
	case ADV7604_PAD_HDMI_PORT_D:
		if (state->edid.present & (1 << edid->pad))
			data = state->edid.edid;
		break;
	default:
		return -EINVAL;
	}

	if (edid->start_block == 0 && edid->blocks == 0) {
		edid->blocks = data ? state->edid.blocks : 0;
		return 0;
	}

	if (!data)
		return -ENODATA;

	if (edid->start_block >= state->edid.blocks)
		return -EINVAL;

	if (edid->start_block + edid->blocks > state->edid.blocks)
		edid->blocks = state->edid.blocks - edid->start_block;

	memcpy(edid->edid, data + edid->start_block * 128, edid->blocks * 128);

	return 0;
}