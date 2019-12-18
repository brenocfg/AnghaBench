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
struct TYPE_4__ {int bytesperline; scalar_t__ pixelformat; } ;
struct TYPE_3__ {int height; int bytesperline; } ;
struct via_camera {int n_cap_bufs; TYPE_2__ user_format; TYPE_1__ sensor_format; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  VCR_CAPINTC ; 
 int VCR_CI_3BUFS ; 
 int VCR_CI_CCIR601_8 ; 
 int VCR_CI_CLKEN ; 
 int VCR_CI_DIBOTH ; 
 int VCR_CI_ENABLE ; 
 int VCR_CI_FLDINV ; 
 int VCR_CI_UYVY ; 
 int VCR_CI_VREFINV ; 
 int VCR_CI_YUYV ; 
 int /*<<< orphan*/  VCR_HORRANGE ; 
 int /*<<< orphan*/  VCR_MAXDATA ; 
 int /*<<< orphan*/  VCR_MAXVBI ; 
 int /*<<< orphan*/  VCR_VERTRANGE ; 
 int /*<<< orphan*/  VCR_VSTRIDE ; 
 int VCR_VS_STRIDE ; 
 int /*<<< orphan*/  viacam_set_scale (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_write_reg (struct via_camera*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void viacam_ctlr_image(struct via_camera *cam)
{
	int cicreg;

	/*
	 * Disable clock before messing with stuff - from the via
	 * sample driver.
	 */
	viacam_write_reg(cam, VCR_CAPINTC, ~(VCR_CI_ENABLE|VCR_CI_CLKEN));
	/*
	 * Set up the controller for VGA resolution, modulo magic
	 * offsets from the via sample driver.
	 */
	viacam_write_reg(cam, VCR_HORRANGE, 0x06200120);
	viacam_write_reg(cam, VCR_VERTRANGE, 0x01de0000);
	viacam_set_scale(cam);
	/*
	 * Image size info.
	 */
	viacam_write_reg(cam, VCR_MAXDATA,
			(cam->sensor_format.height << 16) |
			(cam->sensor_format.bytesperline >> 3));
	viacam_write_reg(cam, VCR_MAXVBI, 0);
	viacam_write_reg(cam, VCR_VSTRIDE,
			cam->user_format.bytesperline & VCR_VS_STRIDE);
	/*
	 * Set up the capture interface control register,
	 * everything but the "go" bit.
	 *
	 * The FIFO threshold is a bit of a magic number; 8 is what
	 * VIA's sample code uses.
	 */
	cicreg = VCR_CI_CLKEN |
		0x08000000 |		/* FIFO threshold */
		VCR_CI_FLDINV |		/* OLPC-specific? */
		VCR_CI_VREFINV |	/* OLPC-specific? */
		VCR_CI_DIBOTH |		/* Capture both fields */
		VCR_CI_CCIR601_8;
	if (cam->n_cap_bufs == 3)
		cicreg |= VCR_CI_3BUFS;
	/*
	 * YUV formats need different byte swapping than RGB.
	 */
	if (cam->user_format.pixelformat == V4L2_PIX_FMT_YUYV)
		cicreg |= VCR_CI_YUYV;
	else
		cicreg |= VCR_CI_UYVY;
	viacam_write_reg(cam, VCR_CAPINTC, cicreg);
}