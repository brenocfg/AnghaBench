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
struct graphics_object_id {scalar_t__ type; int id; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
#define  CONNECTOR_ID_DISPLAY_PORT 142 
#define  CONNECTOR_ID_DUAL_LINK_DVID 141 
#define  CONNECTOR_ID_DUAL_LINK_DVII 140 
#define  CONNECTOR_ID_EDP 139 
#define  CONNECTOR_ID_HDMI_TYPE_A 138 
#define  CONNECTOR_ID_LVDS 137 
#define  CONNECTOR_ID_SINGLE_LINK_DVID 136 
#define  CONNECTOR_ID_SINGLE_LINK_DVII 135 
#define  CONNECTOR_ID_VGA 134 
#define  ENCODER_ID_EXTERNAL_NUTMEG 133 
#define  ENCODER_ID_EXTERNAL_TRAVIS 132 
#define  ENCODER_ID_INTERNAL_DAC1 131 
#define  ENCODER_ID_INTERNAL_DAC2 130 
#define  ENCODER_ID_INTERNAL_KLDSCP_DAC1 129 
#define  ENCODER_ID_INTERNAL_KLDSCP_DAC2 128 
 scalar_t__ OBJECT_TYPE_CONNECTOR ; 
 scalar_t__ OBJECT_TYPE_ENCODER ; 
 int SIGNAL_TYPE_DISPLAY_PORT ; 
 int SIGNAL_TYPE_DVI_DUAL_LINK ; 
 int SIGNAL_TYPE_DVI_SINGLE_LINK ; 
 int SIGNAL_TYPE_EDP ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 
 int SIGNAL_TYPE_LVDS ; 
 int SIGNAL_TYPE_NONE ; 
 int SIGNAL_TYPE_RGB ; 

__attribute__((used)) static enum signal_type get_basic_signal_type(
	struct graphics_object_id encoder,
	struct graphics_object_id downstream)
{
	if (downstream.type == OBJECT_TYPE_CONNECTOR) {
		switch (downstream.id) {
		case CONNECTOR_ID_SINGLE_LINK_DVII:
			switch (encoder.id) {
			case ENCODER_ID_INTERNAL_DAC1:
			case ENCODER_ID_INTERNAL_KLDSCP_DAC1:
			case ENCODER_ID_INTERNAL_DAC2:
			case ENCODER_ID_INTERNAL_KLDSCP_DAC2:
				return SIGNAL_TYPE_RGB;
			default:
				return SIGNAL_TYPE_DVI_SINGLE_LINK;
			}
		break;
		case CONNECTOR_ID_DUAL_LINK_DVII:
		{
			switch (encoder.id) {
			case ENCODER_ID_INTERNAL_DAC1:
			case ENCODER_ID_INTERNAL_KLDSCP_DAC1:
			case ENCODER_ID_INTERNAL_DAC2:
			case ENCODER_ID_INTERNAL_KLDSCP_DAC2:
				return SIGNAL_TYPE_RGB;
			default:
				return SIGNAL_TYPE_DVI_DUAL_LINK;
			}
		}
		break;
		case CONNECTOR_ID_SINGLE_LINK_DVID:
			return SIGNAL_TYPE_DVI_SINGLE_LINK;
		case CONNECTOR_ID_DUAL_LINK_DVID:
			return SIGNAL_TYPE_DVI_DUAL_LINK;
		case CONNECTOR_ID_VGA:
			return SIGNAL_TYPE_RGB;
		case CONNECTOR_ID_HDMI_TYPE_A:
			return SIGNAL_TYPE_HDMI_TYPE_A;
		case CONNECTOR_ID_LVDS:
			return SIGNAL_TYPE_LVDS;
		case CONNECTOR_ID_DISPLAY_PORT:
			return SIGNAL_TYPE_DISPLAY_PORT;
		case CONNECTOR_ID_EDP:
			return SIGNAL_TYPE_EDP;
		default:
			return SIGNAL_TYPE_NONE;
		}
	} else if (downstream.type == OBJECT_TYPE_ENCODER) {
		switch (downstream.id) {
		case ENCODER_ID_EXTERNAL_NUTMEG:
		case ENCODER_ID_EXTERNAL_TRAVIS:
			return SIGNAL_TYPE_DISPLAY_PORT;
		default:
			return SIGNAL_TYPE_NONE;
		}
	}

	return SIGNAL_TYPE_NONE;
}