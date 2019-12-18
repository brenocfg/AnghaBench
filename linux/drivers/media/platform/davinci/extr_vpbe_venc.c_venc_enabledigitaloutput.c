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
struct venc_state {scalar_t__ venc_type; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENC_CMPNT ; 
 int /*<<< orphan*/  VENC_CVBS ; 
 int /*<<< orphan*/  VENC_DACSEL ; 
 int /*<<< orphan*/  VENC_DCLKCTL ; 
 int /*<<< orphan*/  VENC_DRGBX1 ; 
 int /*<<< orphan*/  VENC_HINT ; 
 int /*<<< orphan*/  VENC_HSDLY ; 
 int /*<<< orphan*/  VENC_HSPLS ; 
 int /*<<< orphan*/  VENC_HSTART ; 
 int /*<<< orphan*/  VENC_HVALID ; 
 int /*<<< orphan*/  VENC_LCDOUT ; 
 int /*<<< orphan*/  VENC_OSDCLK0 ; 
 int /*<<< orphan*/  VENC_OSDCLK1 ; 
 int /*<<< orphan*/  VENC_SYNCCTL ; 
 int /*<<< orphan*/  VENC_VIDCTL ; 
 int /*<<< orphan*/  VENC_VINT ; 
 int /*<<< orphan*/  VENC_VMOD ; 
 int /*<<< orphan*/  VENC_VSDLY ; 
 int /*<<< orphan*/  VENC_VSPLS ; 
 int /*<<< orphan*/  VENC_VSTART ; 
 int /*<<< orphan*/  VENC_VSTARTA ; 
 int /*<<< orphan*/  VENC_VVALID ; 
 int /*<<< orphan*/  VENC_YCCCTL ; 
 scalar_t__ VPBE_VERSION_3 ; 
 int /*<<< orphan*/  debug ; 
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  venc_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void venc_enabledigitaloutput(struct v4l2_subdev *sd, int benable)
{
	struct venc_state *venc = to_state(sd);

	v4l2_dbg(debug, 2, sd, "venc_enabledigitaloutput\n");

	if (benable) {
		venc_write(sd, VENC_VMOD, 0);
		venc_write(sd, VENC_CVBS, 0);
		venc_write(sd, VENC_LCDOUT, 0);
		venc_write(sd, VENC_HSPLS, 0);
		venc_write(sd, VENC_HSTART, 0);
		venc_write(sd, VENC_HVALID, 0);
		venc_write(sd, VENC_HINT, 0);
		venc_write(sd, VENC_VSPLS, 0);
		venc_write(sd, VENC_VSTART, 0);
		venc_write(sd, VENC_VVALID, 0);
		venc_write(sd, VENC_VINT, 0);
		venc_write(sd, VENC_YCCCTL, 0);
		venc_write(sd, VENC_DACSEL, 0);

	} else {
		venc_write(sd, VENC_VMOD, 0);
		/* disable VCLK output pin enable */
		venc_write(sd, VENC_VIDCTL, 0x141);

		/* Disable output sync pins */
		venc_write(sd, VENC_SYNCCTL, 0);

		/* Disable DCLOCK */
		venc_write(sd, VENC_DCLKCTL, 0);
		venc_write(sd, VENC_DRGBX1, 0x0000057C);

		/* Disable LCD output control (accepting default polarity) */
		venc_write(sd, VENC_LCDOUT, 0);
		if (venc->venc_type != VPBE_VERSION_3)
			venc_write(sd, VENC_CMPNT, 0x100);
		venc_write(sd, VENC_HSPLS, 0);
		venc_write(sd, VENC_HINT, 0);
		venc_write(sd, VENC_HSTART, 0);
		venc_write(sd, VENC_HVALID, 0);

		venc_write(sd, VENC_VSPLS, 0);
		venc_write(sd, VENC_VINT, 0);
		venc_write(sd, VENC_VSTART, 0);
		venc_write(sd, VENC_VVALID, 0);

		venc_write(sd, VENC_HSDLY, 0);
		venc_write(sd, VENC_VSDLY, 0);

		venc_write(sd, VENC_YCCCTL, 0);
		venc_write(sd, VENC_VSTARTA, 0);

		/* Set OSD clock and OSD Sync Adavance registers */
		venc_write(sd, VENC_OSDCLK0, 1);
		venc_write(sd, VENC_OSDCLK1, 2);
	}
}