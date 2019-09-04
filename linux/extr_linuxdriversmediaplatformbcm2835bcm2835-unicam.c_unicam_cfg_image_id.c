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
struct unicam_cfg {int dummy; } ;
struct unicam_device {scalar_t__ bus_type; int virtual_channel; TYPE_1__* fmt; struct unicam_cfg cfg; } ;
struct TYPE_2__ {int csi_dt; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_IDI0 ; 
 scalar_t__ V4L2_MBUS_CSI2 ; 
 int /*<<< orphan*/  reg_write (struct unicam_cfg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unicam_cfg_image_id(struct unicam_device *dev)
{
	struct unicam_cfg *cfg = &dev->cfg;

	if (dev->bus_type == V4L2_MBUS_CSI2) {
		/* CSI2 mode */
		reg_write(cfg, UNICAM_IDI0,
			  (dev->virtual_channel << 6) | dev->fmt->csi_dt);
	} else {
		/* CCP2 mode */
		reg_write(cfg, UNICAM_IDI0, (0x80 | dev->fmt->csi_dt));
	}
}