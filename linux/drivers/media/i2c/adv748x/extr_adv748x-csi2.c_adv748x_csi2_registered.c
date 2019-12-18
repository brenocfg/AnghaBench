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
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct adv748x_csi2* tx; int /*<<< orphan*/  sd; } ;
struct TYPE_3__ {struct adv748x_csi2* tx; int /*<<< orphan*/  sd; } ;
struct adv748x_state {TYPE_2__ hdmi; TYPE_1__ afe; } ;
struct adv748x_csi2 {struct adv748x_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_AFE_SOURCE ; 
 int /*<<< orphan*/  ADV748X_HDMI_SOURCE ; 
 int adv748x_csi2_register_link (struct adv748x_csi2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct adv748x_csi2* adv748x_sd_to_csi2 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  adv_dbg (struct adv748x_state*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_afe_enabled (struct adv748x_state*) ; 
 int /*<<< orphan*/  is_hdmi_enabled (struct adv748x_state*) ; 
 scalar_t__ is_txa (struct adv748x_csi2*) ; 
 int is_txb (struct adv748x_csi2*) ; 

__attribute__((used)) static int adv748x_csi2_registered(struct v4l2_subdev *sd)
{
	struct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	struct adv748x_state *state = tx->state;
	int ret;

	adv_dbg(state, "Registered %s (%s)", is_txa(tx) ? "TXA":"TXB",
			sd->name);

	/*
	 * Link TXA to AFE and HDMI, and TXB to AFE only as TXB cannot output
	 * HDMI.
	 *
	 * The HDMI->TXA link is enabled by default, as is the AFE->TXB one.
	 */
	if (is_afe_enabled(state)) {
		ret = adv748x_csi2_register_link(tx, sd->v4l2_dev,
						 &state->afe.sd,
						 ADV748X_AFE_SOURCE,
						 is_txb(tx));
		if (ret)
			return ret;

		/* TXB can output AFE signals only. */
		if (is_txb(tx))
			state->afe.tx = tx;
	}

	/* Register link to HDMI for TXA only. */
	if (is_txb(tx) || !is_hdmi_enabled(state))
		return 0;

	ret = adv748x_csi2_register_link(tx, sd->v4l2_dev, &state->hdmi.sd,
					 ADV748X_HDMI_SOURCE, true);
	if (ret)
		return ret;

	/* The default HDMI output is TXA. */
	state->hdmi.tx = tx;

	return 0;
}