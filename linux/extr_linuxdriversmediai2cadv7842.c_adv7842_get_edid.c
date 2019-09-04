#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_edid {int pad; int start_block; int blocks; int /*<<< orphan*/  edid; int /*<<< orphan*/  reserved; } ;
struct TYPE_4__ {int /*<<< orphan*/ * edid; int /*<<< orphan*/  present; } ;
struct TYPE_3__ {int present; int /*<<< orphan*/ * edid; } ;
struct adv7842_state {TYPE_2__ vga_edid; TYPE_1__ hdmi_edid; } ;

/* Variables and functions */
#define  ADV7842_EDID_PORT_A 130 
#define  ADV7842_EDID_PORT_B 129 
#define  ADV7842_EDID_PORT_VGA 128 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7842_get_edid(struct v4l2_subdev *sd, struct v4l2_edid *edid)
{
	struct adv7842_state *state = to_state(sd);
	u8 *data = NULL;

	memset(edid->reserved, 0, sizeof(edid->reserved));

	switch (edid->pad) {
	case ADV7842_EDID_PORT_A:
	case ADV7842_EDID_PORT_B:
		if (state->hdmi_edid.present & (0x04 << edid->pad))
			data = state->hdmi_edid.edid;
		break;
	case ADV7842_EDID_PORT_VGA:
		if (state->vga_edid.present)
			data = state->vga_edid.edid;
		break;
	default:
		return -EINVAL;
	}

	if (edid->start_block == 0 && edid->blocks == 0) {
		edid->blocks = data ? 2 : 0;
		return 0;
	}

	if (!data)
		return -ENODATA;

	if (edid->start_block >= 2)
		return -EINVAL;

	if (edid->start_block + edid->blocks > 2)
		edid->blocks = 2 - edid->start_block;

	memcpy(edid->edid, data + edid->start_block * 128, edid->blocks * 128);

	return 0;
}