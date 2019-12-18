#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  bus_width; } ;
struct TYPE_5__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode_reg2; int /*<<< orphan*/  pix_width_ctrl_emb; int /*<<< orphan*/  pix_width_ctrl; int /*<<< orphan*/  data_selection_ctrl; } ;
struct mipid02_dev {TYPE_3__ r; struct v4l2_fwnode_endpoint tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_HSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MODE_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  SELECTION_MANUAL_WIDTH ; 
 int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 

__attribute__((used)) static int mipid02_configure_from_tx(struct mipid02_dev *bridge)
{
	struct v4l2_fwnode_endpoint *ep = &bridge->tx;

	bridge->r.data_selection_ctrl = SELECTION_MANUAL_WIDTH;
	bridge->r.pix_width_ctrl = ep->bus.parallel.bus_width;
	bridge->r.pix_width_ctrl_emb = ep->bus.parallel.bus_width;
	if (ep->bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		bridge->r.mode_reg2 |= MODE_HSYNC_ACTIVE_HIGH;
	if (ep->bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		bridge->r.mode_reg2 |= MODE_VSYNC_ACTIVE_HIGH;

	return 0;
}