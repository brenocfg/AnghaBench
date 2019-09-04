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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct radeon_i2c_bus_rec {int valid; } ;
struct radeon_hpd {int dummy; } ;
struct radeon_device {int dummy; } ;
struct drm_device {TYPE_1__* pdev; struct radeon_device* dev_private; } ;
struct TYPE_2__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_CRT_SUPPORT ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_DFP3_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int CONNECTOR_7PIN_DIN_ENUM_ID1 ; 
 int DRM_MODE_CONNECTOR_9PinDIN ; 
 int DRM_MODE_CONNECTOR_DVID ; 
 int DRM_MODE_CONNECTOR_DVII ; 
 int DRM_MODE_CONNECTOR_HDMIA ; 
 int DRM_MODE_CONNECTOR_LVDS ; 
 int DRM_MODE_CONNECTOR_VGA ; 
 struct radeon_i2c_bus_rec radeon_lookup_i2c_gpio (struct radeon_device*,int) ; 

__attribute__((used)) static bool radeon_atom_apply_quirks(struct drm_device *dev,
				     uint32_t supported_device,
				     int *connector_type,
				     struct radeon_i2c_bus_rec *i2c_bus,
				     uint16_t *line_mux,
				     struct radeon_hpd *hpd)
{

	/* Asus M2A-VM HDMI board lists the DVI port as HDMI */
	if ((dev->pdev->device == 0x791e) &&
	    (dev->pdev->subsystem_vendor == 0x1043) &&
	    (dev->pdev->subsystem_device == 0x826d)) {
		if ((*connector_type == DRM_MODE_CONNECTOR_HDMIA) &&
		    (supported_device == ATOM_DEVICE_DFP3_SUPPORT))
			*connector_type = DRM_MODE_CONNECTOR_DVID;
	}

	/* Asrock RS600 board lists the DVI port as HDMI */
	if ((dev->pdev->device == 0x7941) &&
	    (dev->pdev->subsystem_vendor == 0x1849) &&
	    (dev->pdev->subsystem_device == 0x7941)) {
		if ((*connector_type == DRM_MODE_CONNECTOR_HDMIA) &&
		    (supported_device == ATOM_DEVICE_DFP3_SUPPORT))
			*connector_type = DRM_MODE_CONNECTOR_DVID;
	}

	/* MSI K9A2GM V2/V3 board has no HDMI or DVI */
	if ((dev->pdev->device == 0x796e) &&
	    (dev->pdev->subsystem_vendor == 0x1462) &&
	    (dev->pdev->subsystem_device == 0x7302)) {
		if ((supported_device == ATOM_DEVICE_DFP2_SUPPORT) ||
		    (supported_device == ATOM_DEVICE_DFP3_SUPPORT))
			return false;
	}

	/* a-bit f-i90hd - ciaranm on #radeonhd - this board has no DVI */
	if ((dev->pdev->device == 0x7941) &&
	    (dev->pdev->subsystem_vendor == 0x147b) &&
	    (dev->pdev->subsystem_device == 0x2412)) {
		if (*connector_type == DRM_MODE_CONNECTOR_DVII)
			return false;
	}

	/* Falcon NW laptop lists vga ddc line for LVDS */
	if ((dev->pdev->device == 0x5653) &&
	    (dev->pdev->subsystem_vendor == 0x1462) &&
	    (dev->pdev->subsystem_device == 0x0291)) {
		if (*connector_type == DRM_MODE_CONNECTOR_LVDS) {
			i2c_bus->valid = false;
			*line_mux = 53;
		}
	}

	/* HIS X1300 is DVI+VGA, not DVI+DVI */
	if ((dev->pdev->device == 0x7146) &&
	    (dev->pdev->subsystem_vendor == 0x17af) &&
	    (dev->pdev->subsystem_device == 0x2058)) {
		if (supported_device == ATOM_DEVICE_DFP1_SUPPORT)
			return false;
	}

	/* Gigabyte X1300 is DVI+VGA, not DVI+DVI */
	if ((dev->pdev->device == 0x7142) &&
	    (dev->pdev->subsystem_vendor == 0x1458) &&
	    (dev->pdev->subsystem_device == 0x2134)) {
		if (supported_device == ATOM_DEVICE_DFP1_SUPPORT)
			return false;
	}


	/* Funky macbooks */
	if ((dev->pdev->device == 0x71C5) &&
	    (dev->pdev->subsystem_vendor == 0x106b) &&
	    (dev->pdev->subsystem_device == 0x0080)) {
		if ((supported_device == ATOM_DEVICE_CRT1_SUPPORT) ||
		    (supported_device == ATOM_DEVICE_DFP2_SUPPORT))
			return false;
		if (supported_device == ATOM_DEVICE_CRT2_SUPPORT)
			*line_mux = 0x90;
	}

	/* mac rv630, rv730, others */
	if ((supported_device == ATOM_DEVICE_TV1_SUPPORT) &&
	    (*connector_type == DRM_MODE_CONNECTOR_DVII)) {
		*connector_type = DRM_MODE_CONNECTOR_9PinDIN;
		*line_mux = CONNECTOR_7PIN_DIN_ENUM_ID1;
	}

	/* ASUS HD 3600 XT board lists the DVI port as HDMI */
	if ((dev->pdev->device == 0x9598) &&
	    (dev->pdev->subsystem_vendor == 0x1043) &&
	    (dev->pdev->subsystem_device == 0x01da)) {
		if (*connector_type == DRM_MODE_CONNECTOR_HDMIA) {
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		}
	}

	/* ASUS HD 3600 board lists the DVI port as HDMI */
	if ((dev->pdev->device == 0x9598) &&
	    (dev->pdev->subsystem_vendor == 0x1043) &&
	    (dev->pdev->subsystem_device == 0x01e4)) {
		if (*connector_type == DRM_MODE_CONNECTOR_HDMIA) {
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		}
	}

	/* ASUS HD 3450 board lists the DVI port as HDMI */
	if ((dev->pdev->device == 0x95C5) &&
	    (dev->pdev->subsystem_vendor == 0x1043) &&
	    (dev->pdev->subsystem_device == 0x01e2)) {
		if (*connector_type == DRM_MODE_CONNECTOR_HDMIA) {
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		}
	}

	/* some BIOSes seem to report DAC on HDMI - usually this is a board with
	 * HDMI + VGA reporting as HDMI
	 */
	if (*connector_type == DRM_MODE_CONNECTOR_HDMIA) {
		if (supported_device & (ATOM_DEVICE_CRT_SUPPORT)) {
			*connector_type = DRM_MODE_CONNECTOR_VGA;
			*line_mux = 0;
		}
	}

	/* Acer laptop (Acer TravelMate 5730/5730G) has an HDMI port
	 * on the laptop and a DVI port on the docking station and
	 * both share the same encoder, hpd pin, and ddc line.
	 * So while the bios table is technically correct,
	 * we drop the DVI port here since xrandr has no concept of
	 * encoders and will try and drive both connectors
	 * with different crtcs which isn't possible on the hardware
	 * side and leaves no crtcs for LVDS or VGA.
	 */
	if (((dev->pdev->device == 0x95c4) || (dev->pdev->device == 0x9591)) &&
	    (dev->pdev->subsystem_vendor == 0x1025) &&
	    (dev->pdev->subsystem_device == 0x013c)) {
		if ((*connector_type == DRM_MODE_CONNECTOR_DVII) &&
		    (supported_device == ATOM_DEVICE_DFP1_SUPPORT)) {
			/* actually it's a DVI-D port not DVI-I */
			*connector_type = DRM_MODE_CONNECTOR_DVID;
			return false;
		}
	}

	/* XFX Pine Group device rv730 reports no VGA DDC lines
	 * even though they are wired up to record 0x93
	 */
	if ((dev->pdev->device == 0x9498) &&
	    (dev->pdev->subsystem_vendor == 0x1682) &&
	    (dev->pdev->subsystem_device == 0x2452) &&
	    (i2c_bus->valid == false) &&
	    !(supported_device & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))) {
		struct radeon_device *rdev = dev->dev_private;
		*i2c_bus = radeon_lookup_i2c_gpio(rdev, 0x93);
	}

	/* Fujitsu D3003-S2 board lists DVI-I as DVI-D and VGA */
	if (((dev->pdev->device == 0x9802) ||
	     (dev->pdev->device == 0x9805) ||
	     (dev->pdev->device == 0x9806)) &&
	    (dev->pdev->subsystem_vendor == 0x1734) &&
	    (dev->pdev->subsystem_device == 0x11bd)) {
		if (*connector_type == DRM_MODE_CONNECTOR_VGA) {
			*connector_type = DRM_MODE_CONNECTOR_DVII;
			*line_mux = 0x3103;
		} else if (*connector_type == DRM_MODE_CONNECTOR_DVID) {
			*connector_type = DRM_MODE_CONNECTOR_DVII;
		}
	}

	return true;
}