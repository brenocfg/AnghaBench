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
struct adv7511_state {int /*<<< orphan*/  have_edid0_ctrl; int /*<<< orphan*/  cec_adap; } ;
struct adv7511_edid_detect {int present; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  segment; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_EDID_DETECT ; 
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  adv7511_rd (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  cec_s_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adv7511_state* get_adv7511_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_subdev_notify (struct v4l2_subdev*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void adv7511_notify_no_edid(struct v4l2_subdev *sd)
{
	struct adv7511_state *state = get_adv7511_state(sd);
	struct adv7511_edid_detect ed;

	/* We failed to read the EDID, so send an event for this. */
	ed.present = false;
	ed.segment = adv7511_rd(sd, 0xc4);
	ed.phys_addr = CEC_PHYS_ADDR_INVALID;
	cec_s_phys_addr(state->cec_adap, ed.phys_addr, false);
	v4l2_subdev_notify(sd, ADV7511_EDID_DETECT, (void *)&ed);
	v4l2_ctrl_s_ctrl(state->have_edid0_ctrl, 0x0);
}