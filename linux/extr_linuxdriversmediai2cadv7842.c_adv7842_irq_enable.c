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

/* Variables and functions */
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static void adv7842_irq_enable(struct v4l2_subdev *sd, bool enable)
{
	if (enable) {
		/* Enable SSPD, STDI and CP locked/unlocked interrupts */
		io_write(sd, 0x46, 0x9c);
		/* ESDP_50HZ_DET interrupt */
		io_write(sd, 0x5a, 0x10);
		/* Enable CABLE_DET_A/B_ST (+5v) interrupt */
		io_write(sd, 0x73, 0x03);
		/* Enable V_LOCKED and DE_REGEN_LCK interrupts */
		io_write(sd, 0x78, 0x03);
		/* Enable SDP Standard Detection Change and SDP Video Detected */
		io_write(sd, 0xa0, 0x09);
		/* Enable HDMI_MODE interrupt */
		io_write(sd, 0x69, 0x08);
	} else {
		io_write(sd, 0x46, 0x0);
		io_write(sd, 0x5a, 0x0);
		io_write(sd, 0x73, 0x0);
		io_write(sd, 0x78, 0x0);
		io_write(sd, 0xa0, 0x0);
		io_write(sd, 0x69, 0x0);
	}
}