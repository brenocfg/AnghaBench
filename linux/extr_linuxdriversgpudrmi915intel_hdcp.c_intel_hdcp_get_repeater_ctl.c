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
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int HDCP_DDIA_REP_PRESENT ; 
 int HDCP_DDIA_SHA1_M0 ; 
 int HDCP_DDIB_REP_PRESENT ; 
 int HDCP_DDIB_SHA1_M0 ; 
 int HDCP_DDIC_REP_PRESENT ; 
 int HDCP_DDIC_SHA1_M0 ; 
 int HDCP_DDID_REP_PRESENT ; 
 int HDCP_DDID_SHA1_M0 ; 
 int HDCP_DDIE_REP_PRESENT ; 
 int HDCP_DDIE_SHA1_M0 ; 
#define  PORT_A 132 
#define  PORT_B 131 
#define  PORT_C 130 
#define  PORT_D 129 
#define  PORT_E 128 

__attribute__((used)) static
u32 intel_hdcp_get_repeater_ctl(struct intel_digital_port *intel_dig_port)
{
	enum port port = intel_dig_port->base.port;
	switch (port) {
	case PORT_A:
		return HDCP_DDIA_REP_PRESENT | HDCP_DDIA_SHA1_M0;
	case PORT_B:
		return HDCP_DDIB_REP_PRESENT | HDCP_DDIB_SHA1_M0;
	case PORT_C:
		return HDCP_DDIC_REP_PRESENT | HDCP_DDIC_SHA1_M0;
	case PORT_D:
		return HDCP_DDID_REP_PRESENT | HDCP_DDID_SHA1_M0;
	case PORT_E:
		return HDCP_DDIE_REP_PRESENT | HDCP_DDIE_SHA1_M0;
	default:
		break;
	}
	DRM_ERROR("Unknown port %d\n", port);
	return -EINVAL;
}