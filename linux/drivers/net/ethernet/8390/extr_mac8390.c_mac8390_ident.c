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
struct nubus_rsrc {int dr_sw; int const dr_hw; } ;
typedef  enum mac8390_type { ____Placeholder_mac8390_type } mac8390_type ;

/* Variables and functions */
 int MAC8390_APPLE ; 
 int MAC8390_ASANTE ; 
 int MAC8390_CABLETRON ; 
 int MAC8390_DAYNA ; 
 int MAC8390_FARALLON ; 
 int MAC8390_INTERLAN ; 
 int MAC8390_KINETICS ; 
 int MAC8390_NONE ; 
#define  NUBUS_DRHW_APPLE_SONIC_LC 142 
#define  NUBUS_DRHW_APPLE_SONIC_NB 141 
#define  NUBUS_DRHW_ASANTE_LC 140 
#define  NUBUS_DRHW_CABLETRON 139 
#define  NUBUS_DRHW_INTERLAN 138 
 int const NUBUS_DRHW_SMC9194 ; 
#define  NUBUS_DRHW_SONNET 137 
#define  NUBUS_DRSW_3COM 136 
#define  NUBUS_DRSW_APPLE 135 
#define  NUBUS_DRSW_ASANTE 134 
#define  NUBUS_DRSW_DAYNA 133 
#define  NUBUS_DRSW_DAYNA2 132 
#define  NUBUS_DRSW_DAYNA_LC 131 
#define  NUBUS_DRSW_FARALLON 130 
#define  NUBUS_DRSW_KINETICS 129 
#define  NUBUS_DRSW_TECHWORKS 128 

__attribute__((used)) static enum mac8390_type mac8390_ident(struct nubus_rsrc *fres)
{
	switch (fres->dr_sw) {
	case NUBUS_DRSW_3COM:
		switch (fres->dr_hw) {
		case NUBUS_DRHW_APPLE_SONIC_NB:
		case NUBUS_DRHW_APPLE_SONIC_LC:
		case NUBUS_DRHW_SONNET:
			return MAC8390_NONE;
		default:
			return MAC8390_APPLE;
		}
		break;

	case NUBUS_DRSW_APPLE:
		switch (fres->dr_hw) {
		case NUBUS_DRHW_ASANTE_LC:
			return MAC8390_NONE;
		case NUBUS_DRHW_CABLETRON:
			return MAC8390_CABLETRON;
		default:
			return MAC8390_APPLE;
		}
		break;

	case NUBUS_DRSW_ASANTE:
		return MAC8390_ASANTE;
		break;

	case NUBUS_DRSW_TECHWORKS:
	case NUBUS_DRSW_DAYNA2:
	case NUBUS_DRSW_DAYNA_LC:
		if (fres->dr_hw == NUBUS_DRHW_CABLETRON)
			return MAC8390_CABLETRON;
		else
			return MAC8390_APPLE;
		break;

	case NUBUS_DRSW_FARALLON:
		return MAC8390_FARALLON;
		break;

	case NUBUS_DRSW_KINETICS:
		switch (fres->dr_hw) {
		case NUBUS_DRHW_INTERLAN:
			return MAC8390_INTERLAN;
		default:
			return MAC8390_KINETICS;
		}
		break;

	case NUBUS_DRSW_DAYNA:
		/*
		 * These correspond to Dayna Sonic cards
		 * which use the macsonic driver
		 */
		if (fres->dr_hw == NUBUS_DRHW_SMC9194 ||
		    fres->dr_hw == NUBUS_DRHW_INTERLAN)
			return MAC8390_NONE;
		else
			return MAC8390_DAYNA;
		break;
	}
	return MAC8390_NONE;
}