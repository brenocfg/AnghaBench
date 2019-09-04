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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int MASK_AD9389B_EDID_RDY_INT ; 
 int MASK_AD9389B_HPD_INT ; 
 int MASK_AD9389B_MSEN_INT ; 
 scalar_t__ ad9389b_have_hotplug (struct v4l2_subdev*) ; 
 int ad9389b_rd (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  ad9389b_wr (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static void ad9389b_set_isr(struct v4l2_subdev *sd, bool enable)
{
	u8 irqs = MASK_AD9389B_HPD_INT | MASK_AD9389B_MSEN_INT;
	u8 irqs_rd;
	int retries = 100;

	/* The datasheet says that the EDID ready interrupt should be
	   disabled if there is no hotplug. */
	if (!enable)
		irqs = 0;
	else if (ad9389b_have_hotplug(sd))
		irqs |= MASK_AD9389B_EDID_RDY_INT;

	/*
	 * This i2c write can fail (approx. 1 in 1000 writes). But it
	 * is essential that this register is correct, so retry it
	 * multiple times.
	 *
	 * Note that the i2c write does not report an error, but the readback
	 * clearly shows the wrong value.
	 */
	do {
		ad9389b_wr(sd, 0x94, irqs);
		irqs_rd = ad9389b_rd(sd, 0x94);
	} while (retries-- && irqs_rd != irqs);

	if (irqs_rd != irqs)
		v4l2_err(sd, "Could not set interrupts: hw failure?\n");
}