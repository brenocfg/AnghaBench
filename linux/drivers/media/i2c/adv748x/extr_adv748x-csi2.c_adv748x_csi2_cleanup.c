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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct adv748x_csi2 {int /*<<< orphan*/  ctrl_hdl; TYPE_1__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_tx_enabled (struct adv748x_csi2*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void adv748x_csi2_cleanup(struct adv748x_csi2 *tx)
{
	if (!is_tx_enabled(tx))
		return;

	v4l2_async_unregister_subdev(&tx->sd);
	media_entity_cleanup(&tx->sd.entity);
	v4l2_ctrl_handler_free(&tx->ctrl_hdl);
}