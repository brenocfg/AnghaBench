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
struct sd {int bridge; scalar_t__ snapshot_needs_reset; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  BRIDGE_OV511 132 
#define  BRIDGE_OV511PLUS 131 
#define  BRIDGE_OV518 130 
#define  BRIDGE_OV518PLUS 129 
#define  BRIDGE_OV519 128 
 int /*<<< orphan*/  R51x_SYS_RESET ; 
 int /*<<< orphan*/  R51x_SYS_SNAP ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sd_reset_snapshot(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!sd->snapshot_needs_reset)
		return;

	/* Note it is important that we clear sd->snapshot_needs_reset,
	   before actually clearing the snapshot state in the bridge
	   otherwise we might race with the pkt_scan interrupt handler */
	sd->snapshot_needs_reset = 0;

	switch (sd->bridge) {
	case BRIDGE_OV511:
	case BRIDGE_OV511PLUS:
		reg_w(sd, R51x_SYS_SNAP, 0x02);
		reg_w(sd, R51x_SYS_SNAP, 0x00);
		break;
	case BRIDGE_OV518:
	case BRIDGE_OV518PLUS:
		reg_w(sd, R51x_SYS_SNAP, 0x02); /* Reset */
		reg_w(sd, R51x_SYS_SNAP, 0x01); /* Enable */
		break;
	case BRIDGE_OV519:
		reg_w(sd, R51x_SYS_RESET, 0x40);
		reg_w(sd, R51x_SYS_RESET, 0x00);
		break;
	}
}