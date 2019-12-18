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
struct v4l2_subdev {int dummy; } ;
struct v4l2_edid {int pad; scalar_t__ start_block; int blocks; int /*<<< orphan*/ * edid; int /*<<< orphan*/ * reserved; } ;
struct TYPE_4__ {int present; int /*<<< orphan*/  edid; } ;
struct TYPE_3__ {int present; int /*<<< orphan*/  edid; } ;
struct adv7842_state {TYPE_2__ hdmi_edid; TYPE_1__ vga_edid; int /*<<< orphan*/  aspect_ratio; } ;

/* Variables and functions */
#define  ADV7842_EDID_PORT_A 130 
#define  ADV7842_EDID_PORT_B 129 
#define  ADV7842_EDID_PORT_VGA 128 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  adv7842_s_detect_tx_5v_ctrl (struct v4l2_subdev*) ; 
 int edid_write_hdmi_segment (struct v4l2_subdev*,int) ; 
 int edid_write_vga_segment (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_calc_aspect_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int,int) ; 

__attribute__((used)) static int adv7842_set_edid(struct v4l2_subdev *sd, struct v4l2_edid *e)
{
	struct adv7842_state *state = to_state(sd);
	int err = 0;

	memset(e->reserved, 0, sizeof(e->reserved));

	if (e->pad > ADV7842_EDID_PORT_VGA)
		return -EINVAL;
	if (e->start_block != 0)
		return -EINVAL;
	if (e->blocks > 2) {
		e->blocks = 2;
		return -E2BIG;
	}

	/* todo, per edid */
	state->aspect_ratio = v4l2_calc_aspect_ratio(e->edid[0x15],
			e->edid[0x16]);

	switch (e->pad) {
	case ADV7842_EDID_PORT_VGA:
		memset(&state->vga_edid.edid, 0, 256);
		state->vga_edid.present = e->blocks ? 0x1 : 0x0;
		memcpy(&state->vga_edid.edid, e->edid, 128 * e->blocks);
		err = edid_write_vga_segment(sd);
		break;
	case ADV7842_EDID_PORT_A:
	case ADV7842_EDID_PORT_B:
		memset(&state->hdmi_edid.edid, 0, 256);
		if (e->blocks) {
			state->hdmi_edid.present |= 0x04 << e->pad;
		} else {
			state->hdmi_edid.present &= ~(0x04 << e->pad);
			adv7842_s_detect_tx_5v_ctrl(sd);
		}
		memcpy(&state->hdmi_edid.edid, e->edid, 128 * e->blocks);
		err = edid_write_hdmi_segment(sd, e->pad);
		break;
	default:
		return -EINVAL;
	}
	if (err < 0)
		v4l2_err(sd, "error %d writing edid on port %d\n", err, e->pad);
	return err;
}