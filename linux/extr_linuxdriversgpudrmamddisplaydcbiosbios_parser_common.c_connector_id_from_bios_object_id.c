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
typedef  int uint32_t ;
typedef  enum connector_id { ____Placeholder_connector_id } connector_id ;

/* Variables and functions */
 int CONNECTOR_ID_DISPLAY_PORT ; 
 int CONNECTOR_ID_DUAL_LINK_DVID ; 
 int CONNECTOR_ID_DUAL_LINK_DVII ; 
 int CONNECTOR_ID_EDP ; 
 int CONNECTOR_ID_HARDCODE_DVI ; 
 int CONNECTOR_ID_HDMI_TYPE_A ; 
 int CONNECTOR_ID_LVDS ; 
 int CONNECTOR_ID_MXM ; 
 int CONNECTOR_ID_PCIE ; 
 int CONNECTOR_ID_SINGLE_LINK_DVID ; 
 int CONNECTOR_ID_SINGLE_LINK_DVII ; 
 int CONNECTOR_ID_UNKNOWN ; 
 int CONNECTOR_ID_VGA ; 
#define  CONNECTOR_OBJECT_ID_DISPLAYPORT 139 
#define  CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D 138 
#define  CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I 137 
#define  CONNECTOR_OBJECT_ID_HARDCODE_DVI 136 
#define  CONNECTOR_OBJECT_ID_HDMI_TYPE_A 135 
#define  CONNECTOR_OBJECT_ID_LVDS 134 
#define  CONNECTOR_OBJECT_ID_MXM 133 
#define  CONNECTOR_OBJECT_ID_PCIE_CONNECTOR 132 
#define  CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D 131 
#define  CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I 130 
#define  CONNECTOR_OBJECT_ID_VGA 129 
#define  CONNECTOR_OBJECT_ID_eDP 128 
 int gpu_id_from_bios_object_id (int) ; 

__attribute__((used)) static enum connector_id connector_id_from_bios_object_id(
	uint32_t bios_object_id)
{
	uint32_t bios_connector_id = gpu_id_from_bios_object_id(bios_object_id);

	enum connector_id id;

	switch (bios_connector_id) {
	case CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I:
		id = CONNECTOR_ID_SINGLE_LINK_DVII;
		break;
	case CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I:
		id = CONNECTOR_ID_DUAL_LINK_DVII;
		break;
	case CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D:
		id = CONNECTOR_ID_SINGLE_LINK_DVID;
		break;
	case CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D:
		id = CONNECTOR_ID_DUAL_LINK_DVID;
		break;
	case CONNECTOR_OBJECT_ID_VGA:
		id = CONNECTOR_ID_VGA;
		break;
	case CONNECTOR_OBJECT_ID_HDMI_TYPE_A:
		id = CONNECTOR_ID_HDMI_TYPE_A;
		break;
	case CONNECTOR_OBJECT_ID_LVDS:
		id = CONNECTOR_ID_LVDS;
		break;
	case CONNECTOR_OBJECT_ID_PCIE_CONNECTOR:
		id = CONNECTOR_ID_PCIE;
		break;
	case CONNECTOR_OBJECT_ID_HARDCODE_DVI:
		id = CONNECTOR_ID_HARDCODE_DVI;
		break;
	case CONNECTOR_OBJECT_ID_DISPLAYPORT:
		id = CONNECTOR_ID_DISPLAY_PORT;
		break;
	case CONNECTOR_OBJECT_ID_eDP:
		id = CONNECTOR_ID_EDP;
		break;
	case CONNECTOR_OBJECT_ID_MXM:
		id = CONNECTOR_ID_MXM;
		break;
	default:
		id = CONNECTOR_ID_UNKNOWN;
		break;
	}

	return id;
}