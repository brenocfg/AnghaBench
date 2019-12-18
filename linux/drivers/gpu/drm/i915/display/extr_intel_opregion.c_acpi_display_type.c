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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int connector_type; } ;
struct intel_connector {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DISPLAY_TYPE_EXTERNAL_DIGITAL ; 
 int /*<<< orphan*/  ACPI_DISPLAY_TYPE_INTERNAL_DIGITAL ; 
 int /*<<< orphan*/  ACPI_DISPLAY_TYPE_OTHER ; 
 int /*<<< orphan*/  ACPI_DISPLAY_TYPE_TV ; 
 int /*<<< orphan*/  ACPI_DISPLAY_TYPE_VGA ; 
#define  DRM_MODE_CONNECTOR_9PinDIN 144 
#define  DRM_MODE_CONNECTOR_Component 143 
#define  DRM_MODE_CONNECTOR_Composite 142 
#define  DRM_MODE_CONNECTOR_DSI 141 
#define  DRM_MODE_CONNECTOR_DVIA 140 
#define  DRM_MODE_CONNECTOR_DVID 139 
#define  DRM_MODE_CONNECTOR_DVII 138 
#define  DRM_MODE_CONNECTOR_DisplayPort 137 
#define  DRM_MODE_CONNECTOR_HDMIA 136 
#define  DRM_MODE_CONNECTOR_HDMIB 135 
#define  DRM_MODE_CONNECTOR_LVDS 134 
#define  DRM_MODE_CONNECTOR_SVIDEO 133 
#define  DRM_MODE_CONNECTOR_TV 132 
#define  DRM_MODE_CONNECTOR_Unknown 131 
#define  DRM_MODE_CONNECTOR_VGA 130 
#define  DRM_MODE_CONNECTOR_VIRTUAL 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static u32 acpi_display_type(struct intel_connector *connector)
{
	u32 display_type;

	switch (connector->base.connector_type) {
	case DRM_MODE_CONNECTOR_VGA:
	case DRM_MODE_CONNECTOR_DVIA:
		display_type = ACPI_DISPLAY_TYPE_VGA;
		break;
	case DRM_MODE_CONNECTOR_Composite:
	case DRM_MODE_CONNECTOR_SVIDEO:
	case DRM_MODE_CONNECTOR_Component:
	case DRM_MODE_CONNECTOR_9PinDIN:
	case DRM_MODE_CONNECTOR_TV:
		display_type = ACPI_DISPLAY_TYPE_TV;
		break;
	case DRM_MODE_CONNECTOR_DVII:
	case DRM_MODE_CONNECTOR_DVID:
	case DRM_MODE_CONNECTOR_DisplayPort:
	case DRM_MODE_CONNECTOR_HDMIA:
	case DRM_MODE_CONNECTOR_HDMIB:
		display_type = ACPI_DISPLAY_TYPE_EXTERNAL_DIGITAL;
		break;
	case DRM_MODE_CONNECTOR_LVDS:
	case DRM_MODE_CONNECTOR_eDP:
	case DRM_MODE_CONNECTOR_DSI:
		display_type = ACPI_DISPLAY_TYPE_INTERNAL_DIGITAL;
		break;
	case DRM_MODE_CONNECTOR_Unknown:
	case DRM_MODE_CONNECTOR_VIRTUAL:
		display_type = ACPI_DISPLAY_TYPE_OTHER;
		break;
	default:
		MISSING_CASE(connector->base.connector_type);
		display_type = ACPI_DISPLAY_TYPE_OTHER;
		break;
	}

	return display_type;
}