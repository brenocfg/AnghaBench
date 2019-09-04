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
typedef  int u32 ;

/* Variables and functions */
#define  MEDIA_BASE_T 136 
#define  MEDIA_DA_TWINAX 135 
#define  MEDIA_KR 134 
#define  MEDIA_MODULE_FIBER 133 
#define  MEDIA_NOT_PRESENT 132 
#define  MEDIA_SFPP_10G_FIBER 131 
#define  MEDIA_SFP_1G_FIBER 130 
#define  MEDIA_UNSPECIFIED 129 
#define  MEDIA_XFP_FIBER 128 
 int PORT_DA ; 
 int PORT_FIBRE ; 
 int PORT_NONE ; 
 int PORT_OTHER ; 
 int PORT_TP ; 

__attribute__((used)) static int qed_get_port_type(u32 media_type)
{
	int port_type;

	switch (media_type) {
	case MEDIA_SFPP_10G_FIBER:
	case MEDIA_SFP_1G_FIBER:
	case MEDIA_XFP_FIBER:
	case MEDIA_MODULE_FIBER:
	case MEDIA_KR:
		port_type = PORT_FIBRE;
		break;
	case MEDIA_DA_TWINAX:
		port_type = PORT_DA;
		break;
	case MEDIA_BASE_T:
		port_type = PORT_TP;
		break;
	case MEDIA_NOT_PRESENT:
		port_type = PORT_NONE;
		break;
	case MEDIA_UNSPECIFIED:
	default:
		port_type = PORT_OTHER;
		break;
	}
	return port_type;
}