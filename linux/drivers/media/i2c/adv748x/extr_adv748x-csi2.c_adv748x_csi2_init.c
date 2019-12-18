#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct adv748x_state {int /*<<< orphan*/ * endpoints; } ;
struct TYPE_4__ {int /*<<< orphan*/  entity; int /*<<< orphan*/ * internal_ops; int /*<<< orphan*/  fwnode; } ;
struct adv748x_csi2 {size_t port; TYPE_1__ sd; int /*<<< orphan*/  ctrl_hdl; TYPE_2__* pads; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CSI2_NR_PADS ; 
 size_t ADV748X_CSI2_SINK ; 
 size_t ADV748X_CSI2_SOURCE ; 
 int /*<<< orphan*/  MEDIA_ENT_F_VID_IF_BRIDGE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int adv748x_csi2_init_controls (struct adv748x_csi2*) ; 
 int /*<<< orphan*/  adv748x_csi2_internal_ops ; 
 int /*<<< orphan*/  adv748x_csi2_ops ; 
 int /*<<< orphan*/  adv748x_csi2_set_virtual_channel (struct adv748x_csi2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv748x_subdev_init (TYPE_1__*,struct adv748x_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_tx_enabled (struct adv748x_csi2*) ; 
 scalar_t__ is_txa (struct adv748x_csi2*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_fwnode_handle (int /*<<< orphan*/ ) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

int adv748x_csi2_init(struct adv748x_state *state, struct adv748x_csi2 *tx)
{
	int ret;

	if (!is_tx_enabled(tx))
		return 0;

	/* Initialise the virtual channel */
	adv748x_csi2_set_virtual_channel(tx, 0);

	adv748x_subdev_init(&tx->sd, state, &adv748x_csi2_ops,
			    MEDIA_ENT_F_VID_IF_BRIDGE,
			    is_txa(tx) ? "txa" : "txb");

	/* Ensure that matching is based upon the endpoint fwnodes */
	tx->sd.fwnode = of_fwnode_handle(state->endpoints[tx->port]);

	/* Register internal ops for incremental subdev registration */
	tx->sd.internal_ops = &adv748x_csi2_internal_ops;

	tx->pads[ADV748X_CSI2_SINK].flags = MEDIA_PAD_FL_SINK;
	tx->pads[ADV748X_CSI2_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&tx->sd.entity, ADV748X_CSI2_NR_PADS,
				     tx->pads);
	if (ret)
		return ret;

	ret = adv748x_csi2_init_controls(tx);
	if (ret)
		goto err_free_media;

	ret = v4l2_async_register_subdev(&tx->sd);
	if (ret)
		goto err_free_ctrl;

	return 0;

err_free_ctrl:
	v4l2_ctrl_handler_free(&tx->ctrl_hdl);
err_free_media:
	media_entity_cleanup(&tx->sd.entity);

	return ret;
}