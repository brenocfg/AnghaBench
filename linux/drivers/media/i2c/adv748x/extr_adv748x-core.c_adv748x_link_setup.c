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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct media_pad {struct media_entity* entity; } ;
struct media_entity {int dummy; } ;
struct TYPE_4__ {struct adv748x_csi2* tx; } ;
struct TYPE_3__ {struct adv748x_csi2* tx; struct v4l2_subdev sd; } ;
struct adv748x_state {TYPE_2__ hdmi; TYPE_1__ afe; } ;
struct adv748x_csi2 {struct v4l2_subdev* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_IO_10 ; 
 int ADV748X_IO_10_CSI1_EN ; 
 int ADV748X_IO_10_CSI4_EN ; 
 int ADV748X_IO_10_CSI4_IN_SEL_AFE ; 
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 struct adv748x_csi2* adv748x_sd_to_csi2 (struct v4l2_subdev*) ; 
 int io_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ is_txa (struct adv748x_csi2*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct adv748x_state* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv748x_link_setup(struct media_entity *entity,
			      const struct media_pad *local,
			      const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *rsd = media_entity_to_v4l2_subdev(remote->entity);
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct adv748x_state *state = v4l2_get_subdevdata(sd);
	struct adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	bool enable = flags & MEDIA_LNK_FL_ENABLED;
	u8 io10_mask = ADV748X_IO_10_CSI1_EN |
		       ADV748X_IO_10_CSI4_EN |
		       ADV748X_IO_10_CSI4_IN_SEL_AFE;
	u8 io10 = 0;

	/* Refuse to enable multiple links to the same TX at the same time. */
	if (enable && tx->src)
		return -EINVAL;

	/* Set or clear the source (HDMI or AFE) and the current TX. */
	if (rsd == &state->afe.sd)
		state->afe.tx = enable ? tx : NULL;
	else
		state->hdmi.tx = enable ? tx : NULL;

	tx->src = enable ? rsd : NULL;

	if (state->afe.tx) {
		/* AFE Requires TXA enabled, even when output to TXB */
		io10 |= ADV748X_IO_10_CSI4_EN;
		if (is_txa(tx))
			io10 |= ADV748X_IO_10_CSI4_IN_SEL_AFE;
		else
			io10 |= ADV748X_IO_10_CSI1_EN;
	}

	if (state->hdmi.tx)
		io10 |= ADV748X_IO_10_CSI4_EN;

	return io_clrset(state, ADV748X_IO_10, io10_mask, io10);
}