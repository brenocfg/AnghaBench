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
struct adv748x_afe {int /*<<< orphan*/ * pads; } ;

/* Variables and functions */
 size_t ADV748X_AFE_SOURCE ; 
 int ENOLINK ; 
 int adv748x_csi2_set_pixelrate (struct v4l2_subdev*,int) ; 
 struct v4l2_subdev* adv748x_get_remote_sd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_afe_propagate_pixelrate(struct adv748x_afe *afe)
{
	struct v4l2_subdev *tx;

	tx = adv748x_get_remote_sd(&afe->pads[ADV748X_AFE_SOURCE]);
	if (!tx)
		return -ENOLINK;

	/*
	 * The ADV748x ADC sampling frequency is twice the externally supplied
	 * clock whose frequency is required to be 28.63636 MHz. It oversamples
	 * with a factor of 4 resulting in a pixel rate of 14.3180180 MHz.
	 */
	return adv748x_csi2_set_pixelrate(tx, 14318180);
}