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
typedef  int u32 ;
struct dcb_table {int dummy; } ;
struct TYPE_2__ {struct dcb_table dcb; } ;
struct nouveau_drm {TYPE_1__ vbios; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_OUTPUT_TMDS ; 
 int /*<<< orphan*/  fabricate_dcb_output (struct dcb_table*,int /*<<< orphan*/ ,int,int,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nv_match_device (struct drm_device*,int,int,int) ; 

__attribute__((used)) static bool
apply_dcb_encoder_quirks(struct drm_device *dev, int idx, u32 *conn, u32 *conf)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct dcb_table *dcb = &drm->vbios.dcb;

	/* Dell Precision M6300
	 *   DCB entry 2: 02025312 00000010
	 *   DCB entry 3: 02026312 00000020
	 *
	 * Identical, except apparently a different connector on a
	 * different SOR link.  Not a clue how we're supposed to know
	 * which one is in use if it even shares an i2c line...
	 *
	 * Ignore the connector on the second SOR link to prevent
	 * nasty problems until this is sorted (assuming it's not a
	 * VBIOS bug).
	 */
	if (nv_match_device(dev, 0x040d, 0x1028, 0x019b)) {
		if (*conn == 0x02026312 && *conf == 0x00000020)
			return false;
	}

	/* GeForce3 Ti 200
	 *
	 * DCB reports an LVDS output that should be TMDS:
	 *   DCB entry 1: f2005014 ffffffff
	 */
	if (nv_match_device(dev, 0x0201, 0x1462, 0x8851)) {
		if (*conn == 0xf2005014 && *conf == 0xffffffff) {
			fabricate_dcb_output(dcb, DCB_OUTPUT_TMDS, 1, 1, 1);
			return false;
		}
	}

	/* XFX GT-240X-YA
	 *
	 * So many things wrong here, replace the entire encoder table..
	 */
	if (nv_match_device(dev, 0x0ca3, 0x1682, 0x3003)) {
		if (idx == 0) {
			*conn = 0x02001300; /* VGA, connector 1 */
			*conf = 0x00000028;
		} else
		if (idx == 1) {
			*conn = 0x01010312; /* DVI, connector 0 */
			*conf = 0x00020030;
		} else
		if (idx == 2) {
			*conn = 0x01010310; /* VGA, connector 0 */
			*conf = 0x00000028;
		} else
		if (idx == 3) {
			*conn = 0x02022362; /* HDMI, connector 2 */
			*conf = 0x00020010;
		} else {
			*conn = 0x0000000e; /* EOL */
			*conf = 0x00000000;
		}
	}

	/* Some other twisted XFX board (rhbz#694914)
	 *
	 * The DVI/VGA encoder combo that's supposed to represent the
	 * DVI-I connector actually point at two different ones, and
	 * the HDMI connector ends up paired with the VGA instead.
	 *
	 * Connector table is missing anything for VGA at all, pointing it
	 * an invalid conntab entry 2 so we figure it out ourself.
	 */
	if (nv_match_device(dev, 0x0615, 0x1682, 0x2605)) {
		if (idx == 0) {
			*conn = 0x02002300; /* VGA, connector 2 */
			*conf = 0x00000028;
		} else
		if (idx == 1) {
			*conn = 0x01010312; /* DVI, connector 0 */
			*conf = 0x00020030;
		} else
		if (idx == 2) {
			*conn = 0x04020310; /* VGA, connector 0 */
			*conf = 0x00000028;
		} else
		if (idx == 3) {
			*conn = 0x02021322; /* HDMI, connector 1 */
			*conf = 0x00020010;
		} else {
			*conn = 0x0000000e; /* EOL */
			*conf = 0x00000000;
		}
	}

	/* fdo#50830: connector indices for VGA and DVI-I are backwards */
	if (nv_match_device(dev, 0x0421, 0x3842, 0xc793)) {
		if (idx == 0 && *conn == 0x02000300)
			*conn = 0x02011300;
		else
		if (idx == 1 && *conn == 0x04011310)
			*conn = 0x04000310;
		else
		if (idx == 2 && *conn == 0x02011312)
			*conn = 0x02000312;
	}

	return true;
}